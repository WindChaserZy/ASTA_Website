import os
import csv
import codecs
import zipfile
import hashlib
import json
from api import settings
from django.contrib import admin
from django.http import HttpResponse
from database.models import Team, User, Contest, Blog, Tag, Token, Comment, Membership, Application
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
	actions = [Download_Selected]
	search_fields = ('selected',)
class gameAdmin(admin.ModelAdmin):
	actions = [Download_Ranking_Code]
	search_fields = ('selected',)
	
# Register your models here.
admin.site.register(Team, teamAdmin)
admin.site.register(User)
admin.site.register(Contest)
admin.site.register(Blog)
admin.site.register(Tag)
admin.site.register(Token)
admin.site.register(Comment)
admin.site.register(Membership)
admin.site.register(Application)
admin.site.register(RsrvProject)
admin.site.register(RsrvTimeAvailable)
admin.site.register(RsrvTimeUsed)
admin.site.register(Problem)
admin.site.register(ProblemSubmission)
admin.site.register(ProblemJudgeDetail)
admin.site.register(ProblemHighestScore)
admin.site.register(Game, gameAdmin)
admin.site.register(GameAi)
admin.site.register(GameBot)
admin.site.register(GameRecord)
admin.site.register(GameBotPlay)