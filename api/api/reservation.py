import datetime
from django.http import HttpResponse
from django.shortcuts import render, redirect
from database.models import User, Contest, Team, RsrvProject, RsrvTimeAvailable, RsrvTimeUsed
from django.contrib import auth
from django.db.models import Q
from api import tools
import json
from api import settings


def list(request):
	#获取项目列表
	list = RsrvProject.objects.all()
	result = []
	for item in list:
		result.append(tools.rsrvProjectToDict(item))
	return HttpResponse(json.dumps(result), content_type = 'application/json')

def detail(request):
	# 用project的id找到该project对象
	try:
		project = RsrvProject.objects.get(id = int(request.GET.get('id')))
	except:
		return HttpResponse("Project not found.", status = 400)
	return HttpResponse(json.dumps(tools.rsrvProjectToDict(project, True)), content_type = 'application/json')
	
def getData(request):
	SecondADay = 86400
	GetDay = 7
	# 不判定用户登录状态，不登录也可以查看
	# 用project的id找到该project对象
	try:
		project = RsrvProject.objects.get(id = int(request.GET.get('id')))
	except:
		return HttpResponse("Project not found.", status = 400)
	
	# 用timestamp算出startTime、endTime，转成datatime格式
	try:
		startTime = tools.timestamp2datetime(int(request.GET.get('startTime')))
		#提供则使用endTime，否则默认为startTime后7天
		if (request.GET and request.GET.get('endTime')):
			endTime = int(request.GET.get('endTime'))
		else:
			endTime = startTime + (SecondADay * GetDay)
		endTime = tools.timestamp2datetime(endTime)
	except:
		return HttpResponse("Wrong start time or end time.", status = 400)
		
	# 用start_time, end_time与project对象得到availableTime列表
	avaiTimeList = RsrvTimeAvailable.objects.filter(project = project, endTime__gte = startTime, startTime__lte = endTime)
	# 用available列表得到相应的UsedTime列表
	result = []
	for avaiTime in avaiTimeList:
		item = {'available' : tools.avaiTimeToDict(avaiTime), 'used' : []}
		usedTimeList = RsrvTimeUsed.objects.filter(availableTime = avaiTime)
		for usedTime in usedTimeList:
			item['used'].append(tools.usedTimeToDict(usedTime))
		result.append(item)
	# 封装并回传
	return HttpResponse(json.dumps(result), content_type = 'application/json')


def apply(request):
	# 登录了才能申请
	if (request.user and request.user.is_authenticated):
		user = request.user
	else:
		return HttpResponse("Please log in.", status = 400)
	
	# 用availableTime的id找到该开放时间对象
	try:
		avaiTime = RsrvTimeAvailable.objects.get(id = int(request.POST.get('id')))
	except:
		return HttpResponse("Available time not found.", status = 400)
	project = avaiTime.project
	
	
	# 用timestamp算出startTime、endTime
	try:
		startTime = tools.timestamp2datetime(int(request.POST.get('startTime')))
		endTime = tools.timestamp2datetime(int(request.POST.get('endTime')))
		assert startTime < endTime
	except:
		return HttpResponse("Wrong start time or end time.", status = 400)
	
	#检查是否为过去时间
	if (startTime.timestamp() - project.timeLimit <= datetime.datetime.now().timestamp()):
		return HttpResponse("Can't reserve a past time.", status = 400)
	#检查是否在开放时间内
	if (startTime < avaiTime.startTime or endTime > avaiTime.endTime):
		return HttpResponse("The time is not available.")
	
	# 检查是否有未使用的申请时间
	if (project.contest):
		team = tools.getTeamByUserContest(user, project.contest)
		# 跟队伍挂钩的项目必须组了队才能申请
		if (team == None):
			return HttpResponse("Not in a team now.", status = 400)
		else:
			timeUsedList = RsrvTimeUsed.objects.filter(availableTime__project = project, endTime__gt = datetime.datetime.now(), user__in = team.members.all())
			if (len(timeUsedList) >= 1):
				return HttpResponse("Already have a reservation.", status = 400)
	else:
		timeUsedList = RsrvTimeUsed.objects.filter(availableTime__project = project, endTime__gt = datetime.datetime.now(), user = user)
		if (len(timeUsedList) >= 1):
			return HttpResponse("Already have a reservation.", status = 400)
	
	# 检查跟已预约时间是否冲突
	timeUsedList = avaiTime.rsrvtimeused_set.filter(startTime__lt = endTime, endTime__gt = startTime)
	for timeUsed in timeUsedList:
		if timeUsed.startTime < endTime and timeUsed.endTime > startTime:
			return HttpResponse("Conflict with existing reservation.", status = 400)
	
	# 建立新的已预约时间
	newTimeUsed = RsrvTimeUsed(availableTime = avaiTime, startTime = startTime, endTime = endTime, user = request.user)
	newTimeUsed.save()
	return HttpResponse('Apply successfully')

def cancel(request):
	#登录了才能取消自己的申请
	if (request.user and request.user.is_authenticated):
		user = request.user
	else:
		return HttpResponse("Please log in.", status = 400)
	
	# 用id找到该已预约时间对象
	try:
		usedTime = RsrvTimeUsed.objects.get(id = int(request.POST.get('id')))
	except:
		return HttpResponse("Reserved time not found.", status = 400)
	
	# 如果预约已经结束就不能删除
	if (usedTime.endTime < datetime.datetime.now()):
		return HttpResponse("Can't cancel a past reservation.", status = 400)
	if (usedTime.endTime.timestamp() - usedTime.availableTime.project.timeLimit <= datetime.datetime.now().timestamp()):
		return HttpResponse("Can't cancel it.", status = 400)
	
	# 判断权限
	if (usedTime.user != user):
		return HttpResponse("Permission denied.", status = 400)
	
	usedTime.delete()
	return HttpResponse('Cancel successfully')

def getToken(request):
	#登录了才能获取自己的密钥
	if (request.user and request.user.is_authenticated):
		user = request.user
	else:
		return HttpResponse("Please log in.", status = 400)
	
	# 用project的id找到该project对象，定位现在可用的usedTime
	try:
		project = RsrvProject.objects.get(id = int(request.GET.get('id')))
	except:
		return HttpResponse("Project not found.", status = 400)

	usedTime = RsrvTimeUsed.objects.filter(user = user, availableTime__project = project, startTime__lte = datetime.datetime.now(), endTime__gte = datetime.datetime.now())
	
	if (len(usedTime) == 0):
		return HttpResponse("Permission denied.", status = 400)
	usedTime = usedTime[0]
	
	AES = tools.myAES(key = settings.RESERVATION_TOKEN_KEY, iv = settings.RESERVATION_TOKEN_IV)
	return HttpResponse(AES.encrypt(usedTime.startTime, usedTime.endTime))
	