import os
import csv
import codecs
import zipfile
import hashlib
import json
from api import settings
from django.contrib import admin
from django.http import HttpResponse
from database.models import Team, User, Contest, Blog, Material, Tag, Token, Comment, Membership, Application, MComment, MFile
from database.models import RsrvProject, RsrvTimeAvailable, RsrvTimeUsed
from database.models import Problem, ProblemSubmission, ProblemHighestScore, ProblemJudgeDetail
from database.models import Game, GameAi, GameBot, GameRecord, GameBotPlay

def Download_Selected(modeladmin, request, queryset):
	csvPath = settings.MEDIA_ROOT + 'teams.csv'
	csvFile = open(csvPath, 'w', newline='')
	csvWriter = csv.writer(csvFile)
	csvWriter.writerow(('ID', 'TeamName', 'Introduction', 'Username', 'Name', 'Class', 'StudentID', 'Email'))
	for team in queryset:
		csvWriter.writerow((team.id, team.name, team.introduction, team.captain.username, team.captain.name, team.captain.className, team.captain.studentId, team.captain.email))
		for member in team.members.all():
			if member.id!=team.captain.id:
				csvWriter.writerow(('', '', '', member.username, member.name, member.className, member.studentId, member.email))

	csvFile.close()
	
	csvFile = open(csvPath, 'rb')
	respone = HttpResponse(csvFile, content_type='application/octet-stream')
	respone['Content-Disposition'] = 'attachment; filename=teams.csv'
	return respone

Download_Selected.short_description = "Download information selected"

def Download_Ranking_Code(modeladmin, request, queryset):
	zipPath = settings.MEDIA_ROOT + 'files.zip'
	zip = zipfile.ZipFile(zipPath, "w", zipfile.ZIP_DEFLATED)
	for game in queryset:
		botList = GameBot.objects.filter(ai__game = game, ranking = True)
		for bot in botList:
			path = os.path.join(settings.MEDIA_ROOT, bot.code.path)
			zip.write(path, bot.code.name)
	zip.close()

	zipFile = open(zipPath, 'rb')
	respone = HttpResponse(zipFile, content_type='application/octet-stream')
	respone['Content-Disposition'] = 'attachment; filename=bots.zip'
	return respone

Download_Ranking_Code.short_description = "Download ranking code"

class teamAdmin(admin.ModelAdmin):
	list_display = ('name', 'contest', 'captain')
	actions = [Download_Selected]
	search_fields = ('selected',)

class gameAdmin(admin.ModelAdmin):
	actions = [Download_Ranking_Code]
	search_fields = ('selected',)
	list_display = ('name','introduction','timestamp')
	
class materialAdmin(admin.ModelAdmin):
	list_display = ('id', 'title', 'author','timestamp','subject')

class blogAdmin(admin.ModelAdmin):
	list_display = ('id', 'title', 'author','timestamp')

class applicationAdmin(admin.ModelAdmin):
	list_display = ('user','team')

class commentAdmin(admin.ModelAdmin):
	list_display = ('timestamp',  'author', 'blog')

class contestAdmin(admin.ModelAdmin):
	list_display = ('name','introduction','registerTimeUp','timeUp')

class gameAIAdmin(admin.ModelAdmin):
	list_display = ('name','introduction','user','team','game')

class userAdmin(admin.ModelAdmin):
	list_display = ('username','name','studentId')
	
class tagAdmin(admin.ModelAdmin):
	list_display = ('name',)

class tokenAdmin(admin.ModelAdmin):
	list_display = ('email','updateTime')

class memberShipAdmin(admin.ModelAdmin):
	list_display = ('user','team')

class rsrvProjectAdmin(admin.ModelAdmin):
	list_display = ('name','contest','timeLimit')

class rsrvTimeAvailableAdmin(admin.ModelAdmin):
	list_display = ('project','startTime','endTime')

class rsrvTimeUsedAdmin(admin.ModelAdmin):
	list_display = ('user','startTime','endTime')

class problemAdmin(admin.ModelAdmin):
	list_display = ('title','contest','timestamp','author')

class problemSubmissionAdmin(admin.ModelAdmin):
	list_display = ('user','team','problem','score','status','timeUsed','timestamp')

class problemJudgeDetailAdmin(admin.ModelAdmin):
	list_display = ('submittime','username','score','status','timeUsed','memoryUsed')
	def username(self,obj):
		return obj.submission.user
	def submittime(self,obj):
		return obj.submission.timestamp
	
class problemHighestScoreAdmin(admin.ModelAdmin):
	list_display = ('user','team','problem','score')
	def score(self,obj):
		return obj.submission.score

class gameAIAdmin(admin.ModelAdmin):
	list_display = ('name','introduction','user','team','game')

class gameBotAdmin(admin.ModelAdmin):
	list_display = ('ai','timestamp','CompileStatus','score')
	def CompileStatus(self,obj):
		if obj.compileStatus == 0:
			return 'waiting'
		elif obj.compileStatus == 1:
			return 'compiling'
		elif obj.compileStatus == 2:
			return 'fault'
		elif obj.compileStatus == 3:
			return 'succeed'

class gameRecordAdmin(admin.ModelAdmin):
	list_display = ('game','timestamp','timeUsed','status')

class gameBotPlayAdmin(admin.ModelAdmin):
	list_display = ('bot','recordtime','originalScore','oldRankingScore','deltaRankingScore')
	def recordtime(self,obj):
		return obj.record.timestamp

class mCommentAdmin(admin.ModelAdmin):
	list_display = ('timestamp',  'author', 'material')

class mFileAdmin(admin.ModelAdmin):
	list_display = ('title','author','timestamp')

# Register your models here.
admin.site.register(Team, teamAdmin)
admin.site.register(User,userAdmin)
admin.site.register(Contest,contestAdmin)
admin.site.register(Blog,blogAdmin)
admin.site.register(Material,materialAdmin)
admin.site.register(Tag,tagAdmin)
admin.site.register(Token,tokenAdmin)
admin.site.register(Comment,commentAdmin)
admin.site.register(MComment,mCommentAdmin)
admin.site.register(MFile,mFileAdmin)
admin.site.register(Membership,memberShipAdmin)
admin.site.register(Application,applicationAdmin)
admin.site.register(RsrvProject,rsrvProjectAdmin)
admin.site.register(RsrvTimeAvailable,rsrvTimeAvailableAdmin)
admin.site.register(RsrvTimeUsed,rsrvTimeUsedAdmin)
admin.site.register(Problem,problemAdmin)
admin.site.register(ProblemSubmission,problemSubmissionAdmin)
admin.site.register(ProblemJudgeDetail,problemJudgeDetailAdmin)
admin.site.register(ProblemHighestScore,problemHighestScoreAdmin)
admin.site.register(Game, gameAdmin)
admin.site.register(GameAi,gameAIAdmin)
admin.site.register(GameBot,gameBotAdmin)
admin.site.register(GameRecord,gameRecordAdmin)
admin.site.register(GameBotPlay,gameBotPlayAdmin)