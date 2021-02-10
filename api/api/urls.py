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
from api import user, contest, blog, team, reservation, problem, game
from . import scheduler_job

urlpatterns = [
	#mdeditor编辑器用的，目前只发现上传图片有用到
	url(r'mdeditor/', include('mdeditor.urls')),
	
	#媒体文件，多为用户上传的
	url(r'^media/editor/(?P<path>.*)$', serve, {"document_root": os.path.join(settings.MEDIA_ROOT, 'editor')}),
	url(r'^media/avatars/(?P<path>.*)$', serve, {"document_root": os.path.join(settings.MEDIA_ROOT, 'avatars')}),
	
	#静态文件，多为开发者自己整的
	url(r'^static/(?P<path>.*)$', serve, {"document_root": settings.STATIC_ROOT}),
	
	#管理页面
	path('admin/', admin.site.urls),
	
	
	#注册
	path('register/', user.register),
	#登录
	path('login/', user.login),
	#登出
	path('logout/', user.logout),
	#获取用户信息
	path('user/', user.getInfo),
	#发送token到邮箱
	path('sendToken/', user.sendToken),
	#用户修改个人信息
	path('modify/', user.modify),
	#重置密码
	path('resetPassword/', user.resetPassword),
	
	
	#获取单个比赛详细信息
	path('contest/', contest.detail),
	#获取比赛列表
	path('contest/list/', contest.list),
	#获取比赛排行榜
	path('contest/leaderboard/', contest.leaderboard),
	path('contest/leaderboard/count/', contest.leaderboardCount),
	
	
	#获取单个博客详细信息
	path('blog/', blog.detail),
	#获取博客列表
	path('blog/list/', blog.list),
	#发布或修改博客
	path('blog/edit/', blog.edit),
	#删除博客
	path('blog/delete/', blog.delete),
	
	
	#发布评论
	path('comment/add/', blog.addComment),
	#获取评论列表
	path('comment/list/', blog.commentList),
	
	
	#获取单个队伍详细信息
	path('team/', team.detail),
	#获取队伍列表
	path('team/list/', team.list),
	#管理队伍
	path('team/admin/', team.admin),
	#申请加入队伍
	path('team/apply/', team.apply),
	
	
	#获取预约项目信息
	path('reservation/', reservation.detail),
	#获取预约项目预约数据
	path('reservation/data/', reservation.getData),
	#获取预约项目列表
	path('reservation/list/', reservation.list),
	#提出预约申请
	path('reservation/apply/', reservation.apply),
	#取消已申请预约
	path('reservation/cancel/', reservation.cancel),
	#获取预约密钥
	path('reservation/token/', reservation.getToken),

	#题库系统
	path('problem/', problem.detail),
	path('problem/list/', problem.list),
	path('problem/submit/', problem.submit),
	path('submission/', problem.submissionDetail),
	path('submission/code/', problem.submissionCodeDownload),
	path('submission/list/', problem.submissionList),
	path('submission/count/', problem.submissionCount),

	#游戏系统
	path('game/', game.detail),
	path('game/list/', game.list),
	path('game/leaderboard/', game.leaderboard),
	path('game/leaderboard/count/', game.leaderboardCount),
	path('game/ai/', game.aiDetail),
	path('game/ai/modify/', game.aiModify),
	path('game/ai/addbot/', game.aiAddBot),
	path('game/ai/list/', game.aiList),
	path('game/bot/code/', game.botCodeDownload),
	path('game/bot/ranking/', game.botRanking),
	path('game/record/list/', game.recordList),
	path('game/record/count/', game.recordListCount),
]
