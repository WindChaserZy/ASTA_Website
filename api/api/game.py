from django.http import HttpResponse, FileResponse
from django.shortcuts import render, redirect
from database.models import Game, Team, GameAi, GameBot, GameBotPlay, GameRecord
from django.contrib import auth
from judge.tasks import compileBot
from api import settings
from api import tools
import os
import json
import datetime

def list(request):
	#比赛列表，没有任何限�?
	list = Game.objects.all().order_by('-timestamp')
	result = []
	for item in list:
		result.append(tools.gameToDict(item))
	return HttpResponse(json.dumps(result), content_type = 'application/json')

def detail(request):
	#根据id反�?�比赛信�?
	if (request.GET == None or request.GET.get('id') == None):
		return HttpResponse("ID missing.", status = 400)
	try:
		item = Game.objects.get(id = int(request.GET.get('id')))
	except:
		return HttpResponse("Game not found.", status = 400)
		
	result = tools.gameToDict(item, True)
	
	return HttpResponse(json.dumps(result), content_type = 'application/json')

def leaderboard(request):
	if (request.GET == None or request.GET.get('id') == None):
		return HttpResponse("ID missing.", status = 400)
	try:
		item = Game.objects.get(id = int(request.GET.get('id')))
	except:
		return HttpResponse("Game not found.", status = 400)
	
	bots = GameBot.objects.filter(ai__game = item, ranking=True)
	
	board = []
	for bot in bots:
		result = {'id': bot.id, 'name': bot.ai.name, 'introduction': bot.ai.introduction, 'score': bot.score}
		if bot.ai.team:
			team = bot.ai.team
			result['teamId'] = team.id
			result['teamName'] = team.name
			result['captain'] = tools.userToDict(team.captain)
		if bot.ai.user:
			result['user'] = tools.userToDict(bot.ai.user)

		board.append(result)

	board.sort(key=lambda item: item['score'], reverse=True)
	

	for index in range(len(board)):
		if (index>0 and board[index]['score']==board[index-1]['score']):
			board[index]['rank'] = board[index-1]['rank']
		else:
			board[index]['rank'] = index+1

	if (request.GET and request.GET.get('sortField') and request.GET.get('sortOrder')):
		board.sort(key=lambda item: item[request.GET.get('sortField')], reverse=request.GET.get('sortOrder') == 'ascend')

	if (request.GET and request.GET.get('pageSize') and request.GET.get('page')):
		pageSize = int(request.GET.get('pageSize'))
		page = int(request.GET.get('page'))
		board = board[(page-1)*pageSize: page*pageSize]
	return HttpResponse(json.dumps(board), content_type = 'application/json')


def leaderboardCount(request):
	if (request.GET == None or request.GET.get('id') == None):
		return HttpResponse("ID missing.", status = 400)
	try:
		item = Game.objects.get(id = int(request.GET.get('id')))
	except:
		return HttpResponse("Game not found.", status = 400)
	
	botNum = GameBot.objects.filter(ai__game = item, ranking=True).count()
	return HttpResponse(json.dumps({'number': botNum}), content_type = 'application/json')

def aiList(request):
	aiList = GameAi.objects
	
	if (request.GET and request.GET.get('game')):
		try:
			aiList = aiList.filter(game__id = int(request.GET.get('game')))
		except:
			return HttpResponse("Game ID error.", status = 400)

	if (request.GET.get('username')):
		aiList = aiList.filter(user__username = request.GET.get('username'))
	if (request.GET.get('team')):
		aiList = aiList.filter(team__id = request.GET.get('team'))
	
	result = []
	for ai in aiList:
		info = tools.gameAiToDict(ai)
		rankingBot = GameBot.objects.filter(ranking=True, ai = ai)
		if (len(rankingBot)>0):
			info['score'] = rankingBot[0].score
		result.append(info)
	return HttpResponse(json.dumps(result), content_type = 'application/json')

def aiDetail(request):
	if (not request.user.is_authenticated):
		return HttpResponse("Please log in.", status = 400)

	if (request.GET == None or request.GET.get('id') == None):
		return HttpResponse("ID missing.", status = 400)
	try:
		ai = GameAi.objects.get(id = int(request.GET.get('id')))
	except:
		return HttpResponse("AI not found.", status = 400)
	
	if not tools.userHasAiPermission(request.user, ai):
		return HttpResponse("Permission denied.", status = 400)

	result = tools.gameAiToDict(ai)
	result['bot'] = []
	for bot in ai.bot.all():
		result['bot'].append(tools.gameBotToDict(bot))
	return HttpResponse(json.dumps(result), content_type = 'application/json')

def aiModify(request):
	if (request.POST and request.POST.get('id')):
		if (not request.user.is_authenticated):
			return HttpResponse("Please log in.", status = 400)

		try:
			ai = GameAi.objects.get(id = int(request.POST.get('id')))
		except:
			return HttpResponse("AI not found.", status = 400)
		
		if not tools.userHasAiPermission(request.user, ai):
			return HttpResponse("Permission denied.", status = 400)
		
		if request.POST.get('name'):
			ai.name = request.POST.get('name')
		if request.POST.get('introduction'):
			ai.introduction = request.POST.get('introduction')
		ai.save()
		return HttpResponse("Modified successfully.", status = 200)

	else:
		if (request.POST == None or request.POST.get('game') == None):
			return HttpResponse("Game ID missing.", status = 400)
		if (request.POST == None or request.POST.get('name') == None):
			return HttpResponse("AI name missing.", status = 400)
		try:
			game = Game.objects.get(id = int(request.POST.get('game')))
		except:
			return HttpResponse("Game not found.", status = 400)


		name = request.POST.get('name')
		introduction = ''
		if request.POST.get('introduction'):
			introduction = request.POST.get('introduction')
		if game.contest:
			team = tools.getTeamByUserContest(request.user, game.contest)
			if team == None:
				return HttpResponse("Not in a team now.", status = 400)
			GameAi(game=game, name=name, introduction=introduction, team=team).save()
		else:
			GameAi(game=game, name=name, introduction=introduction, user=request.user).save()
		return HttpResponse("Created successfully.", status = 200)
	
def aiAddBot(request):
	if (not request.user.is_authenticated):
		return HttpResponse("Please log in.", status = 400)

	if request.POST == None:
		return HttpResponse("Only POST allowed.", status = 400)
	if request.POST.get('id') == None:
		return HttpResponse("ID missing.", status = 400)
		
	if (request.FILES.get('code')):
		code = request.FILES['code']
	else:
		return HttpResponse("File missing.", status = 400)

	try:
		ai = GameAi.objects.get(id = int(request.POST.get('id')))
	except:
		return HttpResponse("AI not found.", status = 400)
	
	if not tools.userHasAiPermission(request.user, ai):
		return HttpResponse("Permission denied.", status = 400)

	addition = ''
	if request.POST.get('addition'):
		addition = request.POST.get('addition')
	bot = GameBot(ai=ai, addition=addition)
	bot.save()
	bot.code = code
	bot.save()
	compileBot.delay(bot)
	return HttpResponse("Update successfully.", status = 200)

def botCodeDownload(request):
	if (not request.user.is_authenticated):
		return HttpResponse("Please log in.", status = 400)
	if (request.GET and request.GET.get('id')):
		try:
			bot = GameBot.objects.get(id = int(request.GET.get('id')))
		except:
			return HttpResponse("Bot not found.", status = 400)
	else:
		return HttpResponse("ID missing.", status = 400)
	
	if not os.path.exists(bot.code.path):
		return HttpResponse("File not found.", status = 400)

	if not tools.userHasAiPermission(request.user, bot.ai):
		return HttpResponse("Permission Denied.", status = 400)
	
	file = open(bot.code.path, 'rb')
	response = FileResponse(file)
	response['Content-Type'] = 'application/octet-stream'
	response['Content-Disposition'] = 'attachment;filename=' + bot.code.name
	return response

def botRanking(request):
	if (not request.user.is_authenticated):
		return HttpResponse("Please log in.", status = 400)
	if (request.POST and request.POST.get('id')):
		try:
			bot = GameBot.objects.get(id = int(request.POST.get('id')))
		except:
			return HttpResponse("Bot not found.", status = 400)
	else:
		return HttpResponse("ID missing.", status = 400)

	if not tools.userHasAiPermission(request.user, bot.ai):
		return HttpResponse("Permission Denied.", status = 400)
	if bot.compileStatus<3:
		return HttpResponse("Not compiled yet.", status = 400)
	
	oldBot = tools.getBotByUserGame(request.user, bot.ai.game)
	
	if oldBot == bot:
		oldBot.ranking = False
		oldBot.save()
		return HttpResponse("Remove successfully.", status = 200)
	else:
		bot.ranking = True
		bot.score = settings.BASE_SCORE
		bot.save()
		if oldBot:
			oldBot.ranking = False
			oldBot.save()
			return HttpResponse("Update successfully.", status = 200)
		else:
			return HttpResponse("Add successfully.", status = 200)

def getRecordList(request):
	if (request.GET and request.GET.get('bot')):
		try:
			bot = GameBot.objects.get(id = int(request.GET.get('bot')))
		except:
			return HttpResponse("Bot not found.", status = 400)
		record = bot.record

	elif (request.GET and request.GET.get('ai')):
		try:
			ai = GameAi.objects.get(id = int(request.GET.get('ai')))
		except:
			return HttpResponse("AI not found.", status = 400)

		record = GameRecord.objects.none()
		for bot in ai.bot:
			record = record | bot.record

	elif (request.GET and request.GET.get('game')):
		try:
			game = Game.objects.get(id = int(request.GET.get('game')))
		except:
			return HttpResponse("Game not found.", status = 400)
		record = game.record
	else:
		record = GameRecord.objects.all()
	
	return record

def recordListCount(request):
	list = getRecordList(request)
	number = list.count()
	return HttpResponse(json.dumps({'number': number}), content_type = 'application/json')
	
def recordList(request):
	record = getRecordList(request).order_by('-id')
	if (request.GET and request.GET.get('pageSize') and request.GET.get('page')):
		try:
			pageSize = int(request.GET.get('pageSize'))
			page = int(request.GET.get('page'))
			record = record[(page-1)*pageSize: page*pageSize]
		except:
			return HttpResponse("Page error.", status = 400)
	
	result = []
	for item in record:
		result.append(tools.gameRecordToDict(item))
	return HttpResponse(json.dumps(result), content_type = 'application/json')

			


