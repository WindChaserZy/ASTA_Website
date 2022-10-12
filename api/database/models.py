from django.db import models
from django.contrib.auth.models import AbstractUser
import django.utils.timezone as timezone
from mdeditor.fields import MDTextField

# Create your models here.
class User(AbstractUser):
	avatar = models.ImageField(upload_to='avatars', default='avatars/default.png')
	studentId = models.IntegerField(default=0)
	email = models.CharField(max_length=60, default='', blank=True)
	name = models.CharField(max_length=20, default='', blank=True)
	className = models.CharField(max_length=10, default='', blank=True)
	wechatId = models.CharField(max_length=60, default='', blank=True)
	introduction = models.CharField(max_length=1024, default='', blank=True)

class Token(models.Model):
	email = models.CharField(max_length=60, default='', primary_key=True)
	key = models.CharField(max_length=1024, default='')
	updateTime = models.DateTimeField(default=timezone.now)

	
class Tag(models.Model):
	name = models.CharField(max_length=100, primary_key=True)

class Blog(models.Model):
	title = models.CharField(max_length=128, default='')
	author = models.ForeignKey(to=User, on_delete=models.SET_NULL, null=True)
	content = MDTextField()
	timestamp = models.DateTimeField(auto_now_add=True)
	tags = models.ManyToManyField(to=Tag, blank=True)

class Comment(models.Model):
	content = MDTextField()
	timestamp = models.DateTimeField(auto_now_add=True)
	author = models.ForeignKey(to=User, on_delete=models.SET_NULL, null=True)
	blog = models.ForeignKey(to=Blog, on_delete=models.SET_NULL, null=True)


class Contest(models.Model):
	name = models.CharField(max_length=100, default='', blank=True)
	introduction = models.CharField(max_length=1024, default='', blank=True)
	detail = MDTextField(blank=True)
	timestamp = models.DateTimeField(auto_now_add=True)
	limitOfMember = models.IntegerField(default=100)
	registerTimeUp = models.DateTimeField()
	timeUp = models.DateTimeField()

class Team(models.Model):
	name = models.CharField(max_length=100, default='')
	introduction = models.CharField(max_length=1024, default='')
	captain = models.ForeignKey(to=User, on_delete=models.SET_NULL, null=True)
	contest = models.ForeignKey(to=Contest, on_delete=models.SET_NULL, null=True)
	members = models.ManyToManyField(to=User, blank=True, through='Membership', related_name='belong')
	candidates = models.ManyToManyField(to=User, blank=True, through='Application', related_name='apply')

#描述用户和队伍之间的归属关系、申请情况
class Membership(models.Model):
	user = models.ForeignKey(to=User, on_delete=models.CASCADE, null=True)
	team = models.ForeignKey(to=Team, on_delete=models.CASCADE, null=True)
class Application(models.Model):
	user = models.ForeignKey(to=User, on_delete=models.CASCADE, null=True)
	team = models.ForeignKey(to=Team, on_delete=models.CASCADE, null=True)





class Problem(models.Model):
	title = models.CharField(max_length=128, default='')
	weight = models.FloatField(default=1)
	content = MDTextField()
	contest = models.ForeignKey(to=Contest, on_delete=models.SET_NULL, null=True, blank=True, related_name='problems')
	timestamp = models.DateTimeField(default=timezone.now)
	author = models.ForeignKey(to=User, on_delete=models.SET_NULL, null=True, blank=True)

def PS_dirpath(instance, filename):
	fileType = filename.split('.')[-1]
	if (not (fileType in ['cpp', 'zip'])):
		fileType = 'zip'
	return './submission/%08d.%s'%(instance.id, fileType)
class ProblemSubmission(models.Model):
	user = models.ForeignKey(to=User, on_delete=models.SET_NULL, null=True, blank=True)
	team = models.ForeignKey(to=Team, on_delete=models.SET_NULL, null=True, blank=True)
	problem = models.ForeignKey(to=Problem, on_delete=models.SET_NULL, null=True, related_name='submissions')
	timestamp = models.DateTimeField(default=timezone.now)
	score = models.FloatField(default=0)
	status = models.CharField(max_length=20, default='')
	code = models.FileField(upload_to=PS_dirpath, null=True)
	timeUsed = models.FloatField(default=0)

class ProblemJudgeDetail(models.Model):
	submission = models.ForeignKey(to=ProblemSubmission, on_delete=models.CASCADE, null=True, related_name='detail')
	score = models.FloatField(default=0)
	status = models.CharField(max_length=20, default='')
	timeUsed = models.FloatField(default=0)
	memoryUsed = models.IntegerField(default=0)

class ProblemHighestScore(models.Model):
	user = models.ForeignKey(to=User, on_delete=models.CASCADE, null=True, blank=True, related_name='highestScore')
	team = models.ForeignKey(to=Team, on_delete=models.CASCADE, null=True, blank=True, related_name='highestScore')
	problem = models.ForeignKey(to=Problem, on_delete=models.CASCADE, null=True, related_name='highestScore')
	submission = models.ForeignKey(to=ProblemSubmission, on_delete=models.CASCADE, null=True)





class Game(models.Model):
	name = models.CharField(max_length=128, default='')
	introduction = models.CharField(max_length=1024, default='', blank=True)
	detail = MDTextField()
	timestamp = models.DateTimeField(auto_now_add=True)
	contest = models.ForeignKey(to=Contest, on_delete=models.SET_NULL, null=True, blank=True, related_name='game')
	judgeWeight = models.IntegerField(default=0)
	playerNumber = models.IntegerField(default=0)

class GameAi(models.Model):
	name = models.CharField(max_length=128, default='')
	introduction = models.CharField(max_length=1024, default='')
	user = models.ForeignKey(to=User, on_delete=models.CASCADE, null=True, blank=True, related_name='ai')
	team = models.ForeignKey(to=Team, on_delete=models.CASCADE, null=True, blank=True, related_name='ai')
	game = models.ForeignKey(to=Game, on_delete=models.CASCADE, null=True, blank=True, related_name='ai')

def GameBot_dirpath(instance, filename):
	fileType = filename.split('.')[-1]
	if (not (fileType in ['cpp', 'zip'])):
		fileType = 'zip'
	return './bot/%08d.%s'%(instance.id, fileType)
class GameBot(models.Model):
	ai = models.ForeignKey(to=GameAi, on_delete=models.CASCADE, related_name='bot')
	addition = models.CharField(max_length=128, default='', blank=True)
	code = models.FileField(upload_to=GameBot_dirpath, null=True)
	programPath = models.CharField(max_length=256, default='')
	timestamp = models.DateTimeField(auto_now_add=True)
	compileStatus = models.IntegerField(default=0) # 0:waiting   1: compiling   2: fault   3: succeed
	score = models.FloatField(default=0)
	ranking = models.BooleanField(default=False)


class GameRecord(models.Model):
	game = models.ForeignKey(to=Game, on_delete=models.CASCADE, null=True, blank=True, related_name='record')
	timestamp = models.DateTimeField(default=timezone.now)
	timeUsed = models.FloatField(default=0)
	status = models.CharField(max_length=20, default='')
	ranking = models.BooleanField(default=False)
	bot = models.ManyToManyField(to=GameBot, through='GameBotPlay', through_fields=('record', 'bot'), related_name='record')

class GameBotPlay(models.Model):
	bot = models.ForeignKey(to=GameBot, on_delete=models.CASCADE, null=True, blank=True, related_name='botplay')
	record = models.ForeignKey(to=GameRecord, on_delete=models.CASCADE, null=True, blank=True, related_name='botplay')
	originalScore = models.FloatField(default=0)
	oldRankingScore = models.FloatField(default=0)
	deltaRankingScore = models.FloatField(default=0)





#预约系统
class RsrvProject(models.Model):
	contest = models.ForeignKey(to=Contest, on_delete=models.SET_NULL, null=True, blank=True)
	name = models.CharField(max_length=50, default='')
	intro = MDTextField(blank=True)
	haveToken = models.BooleanField(blank=True, default=False)
	#预约需要在开始前多长时间
	timeLimit = models.IntegerField(default=0)

class RsrvTimeAvailable(models.Model):
	project = models.ForeignKey(to=RsrvProject, on_delete=models.SET_NULL, null=True)
	startTime = models.DateTimeField()
	endTime = models.DateTimeField()

class RsrvTimeUsed(models.Model):
	startTime = models.DateTimeField()
	endTime = models.DateTimeField()
	availableTime = models.ForeignKey(to=RsrvTimeAvailable, on_delete=models.SET_NULL, null=True)
	user = models.ForeignKey(to=User, on_delete=models.SET_NULL, null=True)