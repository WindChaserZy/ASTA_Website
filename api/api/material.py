from django.http import HttpResponse, FileResponse
from django.shortcuts import render, redirect
from database.models import Contest, Team, Tag, Blog, Comment, Material, MComment, MFile
from django.contrib import auth
from django.utils.encoding import escape_uri_path
from api import tools
import os
from . import tools
import json

def list(request):
	#如果给了grade就只找对应grade的博客
	Query = Material.objects
	
	#如果给了grade就只找对应grade的博客
	if (request.GET and request.GET.get('grade')):
		Query = Query.filter(grade__contains = request.GET['grade'])	
    
    #如果给了subject就只找对应subject的博客
	if (request.GET and request.GET.get('subject')):
		Query = Query.filter(subject__contains = request.GET['subject'])
	
	#如果给了作者就只找这个作者的
	if (request.GET and request.GET.get('author')):
		Query = Query.filter(author__username = request.GET['author'])
	
	#按时间排序
	list = Query.all().order_by('-timestamp')
	result = []
	for item in list:
		result.append(tools.materialToDict(item))
	#转成json格式发送
	return HttpResponse(json.dumps(result), content_type = 'application/json')

def detail(request):
	#检查有没有给博客的id
	if (request.GET == None or request.GET.get('id') == None):
		return HttpResponse("ID missing.", status = 400)
	
	#检查id是否合法
	id = request.GET.get('id')
	try:
		item = Material.objects.get(id = id)
	except:
		return HttpResponse("Material not found.", status = 400)
	#调用tool里面现成的工具封装博客信息
	return HttpResponse(json.dumps(tools.materialToDict(item, detail=True)), content_type = 'application/json')

def edit(request):
	#未登录用户是不能编辑博客的
	if (not request.user.is_authenticated):
		return HttpResponse("Please log in.", status = 400)
	if (request.POST == None):
		return HttpResponse("Only POST is allowed.", status = 400)
	
	#检查是否给了内容、标题、tag，这里判断方式不同是因为tag可以为空，但是内容、标题不能
	if (not request.POST.get('content')):
		return HttpResponse("Content missing.", status = 400)
	if (not request.POST.get('title')):
		return HttpResponse("Title missing.", status = 400)
	if (not request.POST.get('grade')):
		return HttpResponse("Grade Missing.", status = 400)    
	if (not request.POST.get('subject')):
		return HttpResponse("Subject Missing.", status = 400)

	title = request.POST.get('title')
	content = request.POST.get('content')
	grade = request.POST.get('grade')
	subject = request.POST.get('subject')
	file = request.POST.get('file')
	
	#没有给博客id表示发一篇新的，否则检查有没有这个id的博客
	if (request.POST.get('id') == None):
		material = Material(author = request.user)
		material.save()
	else:
		try:
			material = Material.objects.filter(id = int(request.POST.get('id')))[0]
		except:
			return HttpResponse("Material not found.", status = 400)
	
	#检查是否有权限编辑博客
	if (material.author != request.user):
		return HttpResponse("Permission denied.", status = 400)
	
	material.title = title
	material.content = content
	material.grade = grade
	material.subject = subject
	material.file = file
	material.save()
		
	return HttpResponse("Published successfully.", status = 200)

def delete(request):
	#删除就只是检查一下是否存在、有没有权限
	if (not request.user.is_authenticated):
		return HttpResponse("Please log in.", status = 400)
	if (request.POST == None):
		return HttpResponse("Only POST is allowed.", status = 400)
	
	try:
		material = Material.objects.filter(id = int(request.POST.get('id')))[0]
	except:
		return HttpResponse("Material not found.", status = 400)
	
	if (material.author != request.user):
		return HttpResponse("Permission denied.", status = 400)
	
	material.delete()
	return HttpResponse("Deleted successfully.", status = 200)
	
def MtDownload(request):
	if (not request.user.is_authenticated):
		return HttpResponse("Please log in.", status = 400)
	if (request.GET and request.GET.get('id')):
		try:
			material = Material.objects.get(id = int(request.GET.get('id')))
		except:
			return HttpResponse("Material not found.", status = 400)
	else:
		return HttpResponse("ID missing.", status = 400)
	
	if not os.path.exists(material.file.path):
		return HttpResponse("File not found.", status = 400)
	
	file = open(material.file.path, 'rb')
	response = FileResponse(file)
	response['Content-Type'] = 'application/octet-stream'
	response['Content-Disposition'] = 'attachment;filename=' + material.file.name
	return response

def commentList(request):
	#评论列表，如果给了博客就只看单个博客的评论
	list = []
	if (request.GET and request.GET.get('material')):
		try:
			material = Material.objects.filter(id = int(request.GET.get('material')))[0]
		except:
			return HttpResponse("Material not found.", status = 400)
		list = material.mcomment_set.all()
	else:
		list = MComment.objects.all()
	result = []
	for item in list:
		result.append({'author': item.author.username, 'content': item.content, 'time': item.timestamp.strftime('%Y-%m-%d %H:%M:%S'), 'avatar': 'media/' + str(item.author.avatar)})
	return HttpResponse(json.dumps(result), content_type = 'application/json')

def MFDownload(request):
	if (not request.user.is_authenticated):
		return HttpResponse("Please log in.", status = 400)
	if (request.GET and request.GET.get('id')):
		try:
			mfile = MFile.objects.get(id = int(request.GET.get('id')))
		except:
			return HttpResponse("File not found.", status = 400)
	else:
		return HttpResponse("ID missing.", status = 400)
	
	if not os.path.exists(mfile.file.path):
		return HttpResponse("File not found.", status = 400)
	
	file = open(mfile.file.path, 'rb')
	fileType = mfile.file.name.split('.')[-1]
	response = FileResponse(file)
	response['Content-Type'] = 'application/octet-stream'
	response['Content-Disposition'] = 'attachment;filename={}'.format(escape_uri_path(mfile.title + '.' + fileType))
	return response

def FileList(request):
	list = []
	if(request.GET and request.GET.get('material')):
		try:
			material = Material.objects.filter(id=int(request.GET.get('material')))[0]
		except:
			return HttpResponse("Material not found.",status = 400)
		list = material.mfile_set.all()
	else:
		list= MFile.objects.all()
	result=[]
	for item in list:
		result.append({'title':item.title,'author':item.author.username,'time': item.timestamp.strftime('%Y-%m-%d %H:%M:%S'),'id':item.id})
	return HttpResponse(json.dumps(result),content_type = 'application/json')
	

def addComment(request):
	#发布评论比较简单，就是检查登录状况，检查对应博客是否存在
	if (not request.user.is_authenticated):
		return HttpResponse("Please log in.", status = 400)
	if (request.POST == None):
		return HttpResponse("Only POST is allowed.", status = 400)
	
	if (not request.POST.get('content')):
		return HttpResponse("Content missing.", status = 400)
	try:
		material = Material.objects.filter(id = int(request.POST.get('material')))[0]
	except:
		return HttpResponse("Material not found.", status = 400)
		
	MComment(author = request.user, material = material, content = request.POST.get('content')).save()
	return HttpResponse("Added successfully.", status = 200)

