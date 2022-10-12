from django.http import HttpResponse
from django.shortcuts import render, redirect
from database.models import Contest, Team, Tag, Blog, ProblemSubmission
from django.contrib import auth
from api import tools
import json
import datetime

def list(request):
	#比赛列表，没有任何限制
	list = Contest.objects.all().order_by('-timestamp')
	result = []
	for item in list:
		result.append(tools.contestToDict(item))
	return HttpResponse(json.dumps(result), content_type = 'application/json')

def detail(request):
	#根据id反馈比赛信息
	if (request.GET == None or request.GET.get('id') == None):
		return HttpResponse("ID missing.", status = 400)
	try:
		contest = Contest.objects.get(id = int(request.GET.get('id')))
	except:
		return HttpResponse("Contest not found.", status = 400)
		
	result = tools.contestToDict(contest, True)
	
	return HttpResponse(json.dumps(result), content_type = 'application/json')

def leaderboard(request):
	if (request.GET == None or request.GET.get('id') == None):
		return HttpResponse("ID missing.", status = 400)
	try:
		contest = Contest.objects.get(id = int(request.GET.get('id')))
	except:
		return HttpResponse("Contest not found.", status = 400)
	
	problemNum = contest.problems.count()
	problemList = [item for item in contest.problems.all()]
	def getProblemIndex(problem):
		for index, x in enumerate(problemList):
			if x == problem:
				return index
		return -1
	
	records = tools.getHighestScoreByContest(contest)
	teamList = contest.team_set.order_by('id').all()
	board = [{'teamId': team.id, 'teamName': team.name, 'captain': tools.userToDict(team.captain)} for team in teamList]
	
	for item in board:
		for i in range(problemNum):
			item['score%04d'%i] = [0, 0]
	index = 0
	highestScore = [0]*problemNum
	for record in records:
		while(record.team.id > board[index]['teamId']):
			index += 1
			if (index >= len(board)):
				index = 0
		problemId = getProblemIndex(record.problem)
		score = tools.getSubmissionScore(record.submission, request)
		highestScore[problemId] = max(highestScore[problemId], score)
		board[index]['score%04d'%problemId][1] = score

	for item in board:
		item['totalScore'] = 0
		for i in range(problemNum):
			item['score%04d'%i][0] = item['score%04d'%i][1] * problemList[i].weight
			if (highestScore[i] > 0):
				item['score%04d'%i][0] /= highestScore[i]
			item['totalScore'] += item['score%04d'%i][0]

	board.sort(key=lambda item: item['totalScore'], reverse=True)
	

	for index in range(len(board)):
		if (index>0 and board[index]['totalScore']==board[index-1]['totalScore']):
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
		contest = Contest.objects.get(id = int(request.GET.get('id')))
	except:
		return HttpResponse("Contest not found.", status = 400)
	
	teamNum = contest.team_set.count()
	return HttpResponse(json.dumps({'number': teamNum}), content_type = 'application/json')