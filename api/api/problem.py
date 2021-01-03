import datetime
from django.http import HttpResponse
from django.shortcuts import render, redirect
from database.models import User, Problem, ProblemSubmission, Contest
from django.contrib import auth
from django.db.models import Q
from api import tools
from judge.tasks import problemJudge
import json

def list(request):
	#题目列表
	if (request.GET and request.GET.get('contest')):
		try:
			list = Contest.objects.get(id = int(request.GET.get('contest'))).problems.all()
		except:
			return HttpResponse("Contest error.", status = 400)
	else:
		list = Problem.objects.all()
	result = []
	
	for item in list:
		info = tools.problemToDict(item, False)
		result.append(info)
	return HttpResponse(json.dumps(result), content_type = 'application/json')


def detail(request):
	item = None
	if (request.GET and request.GET.get('id')):
		try:
			item = Problem.objects.get(id = int(request.GET.get('id')))
		except:
			return HttpResponse("Problem not found.", status = 400)
	else:
		return HttpResponse("ID missing.", status = 400)
	
	return HttpResponse(json.dumps(tools.problemToDict(item)), content_type = 'application/json')

def submit(request):
	try:
		assert(request.user.is_authenticated)
	except:
		return HttpResponse("Please log in.", status = 400)
	user = request.user

	if (not request.POST):
		return HttpResponse("Only POST is allowed.", status = 400)

	if (request.POST.get('id')):
		try:
			problem = Problem.objects.get(id = int(request.POST.get('id')))
		except:
			return HttpResponse("Problem not found.", status = 400)
	else:
		return HttpResponse("ID missing.", status = 400)
	
	if (request.FILES.get('file')):
		code = request.FILES['file']
	else:
		return HttpResponse("File missing.", status = 400)
		
	if (code.size > 100*1024):
		return HttpResponse("File can't be larger than 100KB.", status = 400)
	
	submission = ProblemSubmission(user=user, problem=problem, status='Waiting')
	result = {}

	if (request.POST.get('contest')):
		try:
			contest = Contest.objects.get(id = int(request.POST.get('contest')))
		except:
			return HttpResponse("Contest error.", status = 400)
		if (datetime.datetime.now() < contest.timeUp):
			team = tools.getTeamByUserContest(user, contest)
			if (team):
				submission.team = team
				result['inContest'] = True
				
	submission.save()
	submission.code = code
	submission.save()
	problemJudge.delay(submission)
	result['message'] = 'Submitted successfully'
	
	return HttpResponse(json.dumps(result))

def submissionList(request):
	if (request.GET and request.GET.get('contest')):
		try:
			list = tools.getSubmissionByContest(Contest.objects.get(id = int(request.GET.get('contest'))))
		except:
			return HttpResponse("Contest error.", status = 400)
	else:
		list = ProblemSubmission.objects.all()
	list = list.order_by("-id")
	if (request.GET and request.GET.get('sortField') and request.GET.get('sortOrder')):
		if (request.GET.get('sortField') in ['id', 'score']):
			if (request.GET.get('sortOrder') == 'ascend'):
				list = list.order_by(request.GET.get('sortField'))
			elif (request.GET.get('sortOrder') == 'descend'):
				list = list.order_by("-"+request.GET.get('sortField'))

	if (request.GET and request.GET.get('pageSize') and request.GET.get('page')):
		pageSize = int(request.GET.get('pageSize'))
		page = int(request.GET.get('page'))
		list = list[(page-1)*pageSize: page*pageSize]
	result = []
	
	for item in list:
		info = tools.submissionToDict(item, False)
		info['score'] = tools.getSubmissionScore(item)
		result.append(info)
	return HttpResponse(json.dumps(result), content_type = 'application/json')
	
def submissionDetail(request):
	item = None
	if (request.GET and request.GET.get('id')):
		try:
			item = ProblemSubmission.objects.get(id = int(request.GET.get('id')))
		except:
			return HttpResponse("Submission not found.", status = 400)
	else:
		return HttpResponse("ID missing.", status = 400)
	
	if (request.user and request.user.is_authenticated and request.user == item.user):
		result = tools.submissionToDict(item, True)
	else:
		result = tools.submissionToDict(item, False)
	return HttpResponse(json.dumps(result), content_type = 'application/json')

def submissionCount(request):
	if (request.GET and request.GET.get('contest')):
		try:
			list = tools.getSubmissionByContest(Contest.objects.get(id = int(request.GET.get('contest'))))
		except:
			return HttpResponse("Contest error.", status = 400)
	else:
		list = ProblemSubmission.objects
	number = list.count()
	return HttpResponse(json.dumps({'number': number}), content_type = 'application/json')