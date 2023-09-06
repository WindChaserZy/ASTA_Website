"""api URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
	https://docs.djangoproject.com/en/3.0/topics/http/urls/
Examples:
Function views
	1. Add an import:  from my_app import views
	2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
	1. Add an import:  from other_app.views import Home
	2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
	1. Import the include() function: from django.urls import include, path
	2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
import os
from django.contrib import admin
from django.urls import path
from django.conf.urls import url
from django.views.static import serve
from django.urls import include
from api import settings
from . import user, contest, blog, team, reservation, problem, game, material
from . import scheduler_job

urlpatterns = [
	#for mdeditor 
	url(r'mdeditor/', include('mdeditor.urls')),
	
	url(r'^media/editor/(?P<path>.*)$', serve, {"document_root": os.path.join(settings.MEDIA_ROOT, 'editor')}),
	url(r'^media/avatars/(?P<path>.*)$', serve, {"document_root": os.path.join(settings.MEDIA_ROOT, 'avatars')}),
	
	#by 刘笑雨，测试pdf显示
	url(r'^media/(?P<path>.*)$', serve, {"document_root": os.path.join(settings.MEDIA_ROOT)}),

	url(r'^static/(?P<path>.*)$', serve, {"document_root": settings.STATIC_ROOT}),
	
	path('admin/', admin.site.urls),
	
	
	path('register/', user.register),
	path('login/', user.login),
	path('logout/', user.logout),
	#get user info
	path('user/', user.getInfo),
	#send token to mail
	path('sendToken/', user.sendToken),
	#modify personal information
	path('modify/', user.modify),
	path('resetPassword/', user.resetPassword),
	
	
	#get single contest detail
	path('contest/', contest.detail),
	#get info list
	path('contest/list/', contest.list),
	path('contest/leaderboard/', contest.leaderboard),
	path('contest/leaderboard/count/', contest.leaderboardCount),
	
	
	#get single contest detail
	path('blog/', blog.detail),
	#get info list
	path('blog/list/', blog.list),
	path('blog/edit/', blog.edit),
	path('blog/delete/', blog.delete),
	
	path('comment/add/', blog.addComment),
	path('comment/list/', blog.commentList),

	path('material/', material.detail),
	path('material/list/', material.list),
	path('material/edit/', material.edit),
	path('material/delete/', material.delete),
	path('material/download/',material.MtDownload),
	
	path('mcomment/list/',material.commentList),
	path('mcomment/add/',material.addComment),
	path('mfile/list/',material.FileList),
	path('mfile/download/',material.MFDownload),
	
	
	path('team/', team.detail),
	path('team/list/', team.list),
	path('team/list/count/', team.listCount),
	path('team/admin/', team.admin),
	#apply to join a team
	path('team/apply/', team.apply),
	
	
	path('reservation/', reservation.detail),
	path('reservation/data/', reservation.getData),
	path('reservation/list/', reservation.list),
	path('reservation/apply/', reservation.apply),
	path('reservation/cancel/', reservation.cancel),
	path('reservation/token/', reservation.getToken),

	path('problem/', problem.detail),
	path('problem/list/', problem.list),
	path('problem/submit/', problem.submit),
	path('submission/', problem.submissionDetail),
	path('submission/code/', problem.submissionCodeDownload),
	path('submission/list/', problem.submissionList),
	path('submission/count/', problem.submissionCount),

	path('game/', game.detail),
	path('game/list/', game.list),
	path('game/leaderboard/', game.leaderboard),
	path('game/leaderboard/count/', game.leaderboardCount),
	path('game/botList/', game.botList),
	path('game/botList/count/', game.botListCount),
	path('game/ai/', game.aiDetail),
	path('game/ai/modify/', game.aiModify),
	path('game/ai/addbot/', game.aiAddBot),
	path('game/ai/list/', game.aiList),
	path('game/bot/code/', game.botCodeDownload),
	path('game/bot/ranking/', game.botRanking),
	path('game/record/list/', game.recordList),
	path('game/record/count/', game.recordListCount),
	path('game/record/download/', game.recordDownload),
	path('game/record/get/', game.recordGet),
]
