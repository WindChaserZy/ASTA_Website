from database.models import User, Problem, ProblemSubmission, ProblemJudgeDetail
from database.models import Game, GameAi, GameBot, GameBotPlay, GameRecord
from celery.utils.log import get_task_logger
from celery import task, platforms
from celery.task.control import inspect
import os
import tarfile
import subprocess
import numpy as np
import time
from api import tools
from api.settings import BASE_DIR, ScoreUpdateSpeed, GameEps
platforms.C_FORCE_ROOT = True


def compileWork(code, program, uid):
	filetype = code.split('/')[-1].split('.')[-1]
	volumePath = os.path.join(BASE_DIR, 'judge/volume')
	codeName = 'code_' + uid + '.' + filetype
	programName = 'program_' + uid
	subprocess.run(['cp', code, os.path.join(volumePath, codeName)])
	compileProcess = subprocess.Popen(['docker', 'run', '-m', '700m', '--memory-swap', '700m', '-v', volumePath+':/volume',\
								'judge_box', '-j', 'compile', '-c', '/volume/'+codeName, '-p', '/volume/'+programName],\
								encoding='utf-8', stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	try:
		out, err = compileProcess.communicate(timeout=60)
		assert(compileProcess.returncode==0)
		result = out.split()
		assert(len(result)==2)
		subprocess.run(['rm', os.path.join(volumePath, codeName)])
	except subprocess.TimeoutExpired:
		compileProcess.kill()
		out, err = compileProcess.communicate()
		return False, 'SystemTimeout'
	except:
		return False, 'SystemError'
	

	if result[0] == '0':
		return False, result[1]
	try:		
		subprocess.run(['cp', os.path.join(volumePath, programName), program])
		subprocess.run(['rm', os.path.join(volumePath, programName)])
	except:
		return False, 'SystemError'


	return True, ''


@task
def problemJudge(submission):
	if (type(submission).__name__ == 'int'):
		submission = ProblemSubmission.objects.get(id = submission)

	submission.status = "Compiling"
	submission.save()

	uid = 'submission%08d'%submission.id
	programPath = os.path.join(BASE_DIR, 'judge/program/submission', "%08d"%submission.id)
	if not os.path.exists(programPath):
		successful, info = compileWork(submission.code.path, programPath, uid)
		if not successful:
			submission.status = info
			submission.save()
			return
	
	submission.status = "Judging"
	submission.save()
	volumePath = os.path.join(BASE_DIR, 'judge/volume')
	programName = 'program_' + uid
	subprocess.run(['cp', programPath, os.path.join(volumePath, programName)])
	judge = subprocess.Popen([  'docker', 'run', '-m', '700m', '--memory-swap', '700m', '-v', volumePath+':/volume',\
								'judge_box', '-j', 'problem', '-id', str(submission.problem.id), '-p', '/volume/'+programName],\
								encoding='utf-8', stdout=subprocess.PIPE, stderr=subprocess.PIPE)

	try:
		TimeUsed = time.time()
		judgeout, judgeerr = judge.communicate(timeout=60)
		TimeUsed = time.time() - TimeUsed
		submission.timeUsed = TimeUsed
		submission.save()
		assert(judge.returncode==0)
	except subprocess.TimeoutExpired:
		judge.kill()
		judgeout, judgeerr = judge.communicate()
		result = ' '.join(['Final', 'SystemTimeout', '0', '0'])
	except:
		result = ' '.join(['Final', 'SystemError', '0', '0'])
	else:
		result = judgeout
	
		
	subprocess.run(['rm', os.path.join(volumePath, programName)])

	try:
		for s in result.split('\n'):
			detail = s.split()
			if len(detail) < 4:
				continue
			if detail[0] == 'Final':
				submission.status = detail[1]
				submission.score = float(detail[2])
			else:
				point = ProblemJudgeDetail(submission=submission)
				point.status = detail[0]
				point.score = float(detail[1])
				point.timeUsed = float(detail[2])
				point.memoryUsed = int(detail[3])
				point.save()
		submission.save()
	except:
		submission.detail.all().delete()
		submission.status = 'SystemError'
		submission.save()
	else:
		tools.updateHighestScore(submission)
		if (submission.team):
			tools.updateHighestScore(submission, True)
@task
def compileBot(bot):
	if (type(bot).__name__ == 'int'):
		bot = GameBot.objects.get(id = bot)
	bot.compileStatus = 1
	bot.save()
	programPath = os.path.join(BASE_DIR, 'judge/program/bot', "%08d"%bot.id)
	successful, info = compileWork(bot.code.path, programPath, 'bot%08d'%bot.id)
	print(successful, info)
	if successful:
		bot.compileStatus = 3
		bot.programPath = programPath
	else:
		bot.compileStatus = 2
	bot.save()

def setGameJudgeWeight(game, weight):
	if (type(game).__name__ == 'int'):
		game = Game.objects.get(id = game)
	
	game.judgeWeight = weight
	game.save()

def gameJudge(game, bots, uid):
	if (type(game).__name__ == 'int'):
		game = Game.objects.get(id = game)
	
	botList = []
	programList = []
	programListVolumn = []
	for bot in bots:
		if (type(bot).__name__ == 'int'):
			bot = GameBot.objects.get(id = bot)
		botList.append(bot)
		programList.append(bot.programPath)

	volumePath = os.path.join(BASE_DIR, 'judge/volume')
	for i in range(game.playerNumber):
		programName = ('%04d_'%i) + uid
		subprocess.run(['cp', programList[i], os.path.join(volumePath, programName)])
		programListVolumn.append('/volume/'+programName)
	

	gameProcess = subprocess.Popen(['docker', 'run', '-m', '700m', '--memory-swap', '700m', '-v', volumePath+':/volume',\
									'judge_box', '-j', 'game', '-id', str(game.id), '-p'] + programListVolumn,\
									encoding='utf-8', stdout=subprocess.PIPE, stderr=subprocess.PIPE)

	try:
		out, err = gameProcess.communicate(timeout=300)
		for i in range(game.playerNumber):
			programName = ('%04d_'%i) + uid
			subprocess.run(['rm', os.path.join(volumePath, programName)])
		assert(gameProcess.returncode==0)
		result = [float(x) for x in out.split()]
		assert(len(result) == game.playerNumber)
	except subprocess.TimeoutExpired:
		gameProcess.kill()
		out, err = gameProcess.communicate()
		return False, "SystemTimeout"
	except:
		return False, "SystemError"
	else:
		return True, result
	

@task
def gameRecordJudge(gameRecord):
	if (type(gameRecord).__name__ == 'int'):
		gameRecord = GameRecord.objects.get(id = gameRecord)

	gameRecord.status = "Judging"
	gameRecord.save()
	bpList = gameRecord.botplay.all()
	programList = []
	rankingScoreSum = 0
	originalScoreSum = 0
	uid = 'record%08d'%gameRecord.id


	for bp in bpList:
		programList.append(bp.bot.programPath)
		bp.oldRankingScore = bp.bot.score
		bp.save()
		rankingScoreSum += bp.oldRankingScore

	startTime = time.time()
	successful, result = gameJudge(gameRecord.game, [bp.bot for bp in bpList], uid)
	gameRecord.timeUsed = time.time() - startTime
	if not successful:
		gameRecord.status = result
		gameRecord.save()
		return

	score = np.array(result) + GameEps
	originalScoreSum = np.sum(score)
	for i in range(gameRecord.game.playerNumber):
		bp = bpList[i]
		bp.originalScore = score[i]
		targetScore = bp.originalScore / originalScoreSum * rankingScoreSum
		bp.deltaRankingScore = (targetScore - bp.oldRankingScore) * ScoreUpdateSpeed
		bp.save()
		if gameRecord.ranking:
			bp.bot.score += bp.deltaRankingScore
			bp.bot.save()

	gameRecord.status = "Finish"
	gameRecord.save()
	
def randomRankingGame():
	status = inspect().active()
	for key in status:
		if len(status[key]) > 0:
			return
	

	gameList = Game.objects.all()
	weight = np.array([game.judgeWeight for game in gameList])
	if sum(weight) < 1e-9:
		return
	game = np.random.choice(gameList, p=weight/sum(weight))
	botList = GameBot.objects.filter(ai__game = game, ranking = True)
	if len(botList) < game.playerNumber:
		return
	bots = np.random.choice(botList, size = game.playerNumber, replace = False)

	record = GameRecord(game=game, status="Waiting", ranking=True)
	record.save()
	for bot in bots:
		GameBotPlay(bot=bot, record=record).save()
	gameRecordJudge.delay(record)
