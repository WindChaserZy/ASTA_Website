from database.models import User, Team, Blog, Tag, Material
from database.models import RsrvProject, RsrvTimeAvailable, RsrvTimeUsed
from database.models import Problem, ProblemSubmission, ProblemHighestScore, ProblemJudgeDetail
from database.models import Game, GameAi, GameBot, GameRecord
import json
import base64
import datetime
from Crypto.Cipher import AES

#一些简单的工具，主要是把类�?成字典或者json字�?�串的工�?
class myAES:
    def __init__(self, key, iv):
        self.key = key
        self.iv = iv

    def encrypt(self, start, end):
        #输入两个时间，加密为字�?�串
        text = str(start.timestamp())+' '+str(end.timestamp())
        l = len(text)&15
        if l>0:
            text += ' '*(16-l)
        self.aes = AES.new(self.key, AES.MODE_CBC, self.iv)
        res = self.aes.encrypt(text.encode('utf-8'))
        res_b64 = base64.b64encode(res)
        return res_b64

    def decrypt(self, text):
        #输入密文解密为开始、结束时�?
        self.aes = AES.new(self.key, AES.MODE_CBC, self.iv)
        text = self.aes.decrypt(base64.b64decode(text))
        start, end = [datetime.fromtimestamp(float(a)) for a in text.split()]
        return start, end


def timestamp2datetime(dateTime):
	return datetime.datetime.fromtimestamp(dateTime/1000)
def datetime2timestamp(dateTime):
	return int(dateTime*1000)

def userToDict(user, detail = False):
	result = {}
	if detail:
		result['studentId'] = user.studentId
		result['email'] = user.email
		result['name'] = user.name
		result['className'] = user.className
		result['wechatId'] = user.wechatId
		result['isStaff'] = user.is_staff

	result['id'] = user.id
	result['email'] = user.email
	result['name'] = user.name
	result['className'] = user.className
	result['avatar'] = 'media/' + str(user.avatar)
	result['username'] = user.username
	result['introduction'] = user.introduction
	return result

def userToJson(user, detail = False):
	return json.dumps(userToDict(user, detail))

def contestToDict(contest, detail = False):
	result = {}
	result['id'] = contest.id
	result['name'] = contest.name
	result['introduction'] = contest.introduction
	result['register'] = datetime.datetime.now() <= contest.registerTimeUp
	result['going'] = datetime.datetime.now() <= contest.timeUp
	if (detail):
		result['detail'] = contest.detail
		result['problems'] = [problemToDict(item, False) for item in contest.problems.all()]
	return result

def gameToDict(game, detail = False):
	result = {}
	result['id'] = game.id
	result['name'] = game.name
	result['introduction'] = game.introduction
	result['date'] = game.timestamp.strftime('%Y-%m-%d %H:%M:%S')
	if (game.contest):
		result['contest'] = game.contest.id
	if (detail):
		result['detail'] = game.detail
	return result

def gameAiToDict(gameAi):
	result = {}
	result['id'] = gameAi.id
	result['name'] = gameAi.name
	result['introduction'] = gameAi.introduction
	if gameAi.user:
		result['user'] = userToDict(gameAi.user)
	if gameAi.team:
		result['team'] = teamToDict(gameAi.team)
		result['captain'] = userToDict(gameAi.team.captain)

	return result

def gameBotToDict(gameBot, detail = False):
	result = {}
	result['id'] = gameBot.id
	result['date'] = gameBot.timestamp.strftime('%Y-%m-%d %H:%M:%S')
	if detail:
		result['addition'] = gameBot.addition
		result['compileStatus'] = gameBot.compileStatus
		result['ranking'] = gameBot.ranking
	return result

def gameRecordToDict(gameRecord, detail = False):
	result = {}
	result['id'] = gameRecord.id
	result['game'] = {'id': gameRecord.game.id, 'name': gameRecord.game.name}
	result['date'] = gameRecord.timestamp.strftime('%Y-%m-%d %H:%M:%S')
	result['time'] = gameRecord.timeUsed
	result['status'] = gameRecord.status
	result['ranking'] = gameRecord.ranking
	result['bot'] = []
	for botPlay in gameRecord.botplay.all():
		result['bot'].append({	'id': botPlay.bot.id, \
								'ai': gameAiToDict(botPlay.bot.ai), \
								'oldRankingScore': botPlay.oldRankingScore, \
								'deltaRankingScore': botPlay.deltaRankingScore, \
								'originalScore': botPlay.originalScore})
	return result

def usedTimeToDict(usedTime):
	result = {}
	result['id'] = usedTime.id
	result['startTime'] = datetime2timestamp(usedTime.startTime.timestamp())
	result['endTime'] = datetime2timestamp(usedTime.endTime.timestamp())
	result['user'] = usedTime.user.id
	return result

def avaiTimeToDict(avaiTime):
	result = {}
	result['id'] = avaiTime.id
	result['startTime'] = datetime2timestamp(avaiTime.startTime.timestamp())
	result['endTime'] = datetime2timestamp(avaiTime.endTime.timestamp())
	return result

def rsrvProjectToDict(project, detail = False):
	result = {}
	result['id'] = project.id
	result['name'] = project.name
	result['haveToken'] = project.haveToken
	if detail:
		result['introduction'] = project.intro
	if project.contest:
		result['contest'] = project.contest.id
	return result

def teamToDict(team, detail = False):
	result = {'id': team.id, 'name': team.name, 'introduction': team.introduction, 'captain': team.captain.username, 'members': [], 'candidates': []}
	if detail:
		candidateList = team.candidates.all()
		for candidate in candidateList:
			result['candidates'].append(userToDict(candidate, True))

	memberList = team.members.all()
	for member in memberList:
		if not member==team.captain:
			result['members'].append(userToDict(member, detail))

	return result

def teamToJson(team, detail = False):
	return json.dumps(teamToDict(team, detail))

def blogToDict(blog, detail=False):
	result = {}
	result['id'] = blog.id
	result['title'] = blog.title
	result['author'] = blog.author.username
	result['time'] = blog.timestamp.strftime('%Y-%m-%d %H:%M:%S')
	result['tags'] = []
	tags = blog.tags.all()
	for tag in tags:
		result['tags'].append(tag.name)
	if detail:
		result['content'] = blog.content
	return result

def materialToDict(material, detail=False):
	result = {}
	result['id'] = material.id
	result['title'] = material.title
	result['author'] = material.author.username
	result['time'] = material.timestamp.strftime('%Y-%m-%d %H:%M:%S')
	result['grade'] = material.grade
	result['subject'] = material.subject
	if detail:
		result['content'] = material.content
	return result

def problemToDict(problem, detail = True):
	result = {}
	result['id'] = problem.id
	result['title'] = problem.title
	if (problem.author):
		result['author'] = problem.author.username
	else:
		result['author'] = User.objects.get(id = 1).username
	result['time'] = problem.timestamp.strftime('%Y-%m-%d %H:%M:%S')
	if detail:
		result['content'] = problem.content
	return result

def submissionToDict(submission, detail = False):
	result = {}
	result['id'] = submission.id
	result['problem'] = {'id': submission.problem.id, 'title': submission.problem.title}
	result['user'] = submission.user.username
	result['date'] = submission.timestamp.strftime('%Y-%m-%d %H:%M:%S')
	result['time'] = submission.timeUsed
	result['score'] = submission.score
	result['status'] = submission.status
	if submission.team:
		result['team'] = submission.team.name
	if detail:
		result['code'] = 'media/' + str(submission.code)
	return result

def judgeDetailToDict(judgeDetail, detail = False):
	result = {}
	result['time'] = judgeDetail.timeUsed
	result['memory'] = judgeDetail.memoryUsed
	result['score'] = judgeDetail.score
	result['status'] = judgeDetail.status
	return result


def getTeamByUsernameContestid(username, contestID):
	return User.objects.get(username = username).belong.filter(contest__id = contestID)

def getTeamByUserContest(user, contest):
	team = user.belong.filter(contest = contest)
	if len(team) == 0:
		return None
	else:
		return team[0]

def updateHighestScore(submission, inContest = False):
	if (submission.score < 0):
		return
	if (inContest):
		record = ProblemHighestScore.objects.filter(team = submission.team, problem = submission.problem)
	else:
		record = ProblemHighestScore.objects.filter(user = submission.user, team__isnull = True, problem = submission.problem)

	if (record.count() == 0):
		team = None
		if (inContest):
			team = submission.team

		ProblemHighestScore(user = submission.user, problem = submission.problem, team = team, submission = submission).save()
	elif (record[0].submission.score < submission.score):
		s = record[0]
		s.submission = submission
		s.save()

def isProblemOpen(problem, request = None):
	if (request and request.user.is_authenticated and request.user.is_staff):
		return True

	if (problem.timestamp < datetime.datetime.now()):
		return True

	return False

def getSubmissionScore(submission, request = None):
	if isProblemOpen(submission.problem, request):
		return submission.score
	else:
		return 0

def getHighestScoreByContest(contest):
	records = ProblemHighestScore.objects.none()
	for problem in contest.problems.all():
		records = records | problem.highestScore.filter(team__isnull = False).order_by('team__id').all()
	return records

def getSubmissionByContest(contest):
	records = ProblemSubmission.objects.none()
	for problem in contest.problems.all():
		records = records | problem.submissions.filter(team__isnull = False).order_by('team__id').all()
	return records

def isUserInTeam(user, team):
	return user in team.members.all()

def userHasAiPermission(user, game):
	if (user.is_staff):
		return True
	if (game.user and game.user!=user):
		return False

	if (game.team and isUserInTeam(user, game.team)==False):
		return False

	return True

def getBotByUserGame(user, game):
	if game.contest:
		team = getTeamByUserContest(user, game.contest)
		if team:
			bot = GameBot.objects.filter(ai__team = team, ranking=True)
		else:
			return None
	else:
		bot = GameBot.objects.filter(ai__user = user, ranking=True)

	if len(bot):
		return bot[0]
	else:
		return None
