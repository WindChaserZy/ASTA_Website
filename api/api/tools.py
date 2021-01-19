from database.models import User, Team, Blog, Tag, RsrvProject, RsrvTimeAvailable, RsrvTimeUsed, Problem, ProblemSubmission, ProblemHighestScore
import json
import base64
import datetime
from Crypto.Cipher import AES

#一些简单的工具，主要是把类转成字典或者json字符串的工具
class myAES:
    def __init__(self, key, iv):
        self.key = key
        self.iv = iv
    
    def encrypt(self, start, end):
        #输入两个时间，加密为字符串
        text = str(start.timestamp())+' '+str(end.timestamp())
        l = len(text)&15
        if l>0:
            text += ' '*(16-l)
        self.aes = AES.new(self.key, AES.MODE_CBC, self.iv)
        res = self.aes.encrypt(text.encode('utf-8'))
        res_b64 = base64.b64encode(res)
        return res_b64
    
    def decrypt(self, text):
        #输入密文解密为开始、结束时间
        self.aes = AES.new(self.key, AES.MODE_CBC, self.iv)
        text = self.aes.decrypt(base64.b64decode(text))
        start, end = [datetime.fromtimestamp(float(a)) for a in text.split()]
        return start, end


def timestamp2datetime(dateTime):
	return datetime.datetime.fromtimestamp(dateTime/1000)
def datetime2timestamp(dateTime):
	return int(dateTime*1000)

def userToDict(user, detail = False):
	result = {}
	if detail:
		result['studentId'] = user.studentId
		result['email'] = user.email
		result['name'] = user.name
		result['className'] = user.className
		result['isStaff'] = user.is_staff
		
	result['id'] = user.id
	result['avatar'] = 'media/' + str(user.avatar)
	result['username'] = user.username
	return result
	
def userToJson(user, detail = False):
	return json.dumps(userToDict(user, detail))

def contestToDict(contest, detail = False):
	result = {}
	result['id'] = contest.id
	result['name'] = contest.name
	result['introduction'] = contest.introduction
	result['register'] = datetime.datetime.now() <= contest.registerTimeUp
	result['going'] = datetime.datetime.now() <= contest.timeUp
	if (detail):
		result['detail'] = contest.detail
		result['problems'] = [problemToDict(item, False) for item in contest.problems.all()]
	return result

def usedTimeToDict(usedTime):
	result = {}
	result['id'] = usedTime.id
	result['startTime'] = datetime2timestamp(usedTime.startTime.timestamp())
	result['endTime'] = datetime2timestamp(usedTime.endTime.timestamp())
	result['user'] = usedTime.user.id
	return result

def avaiTimeToDict(avaiTime):
	result = {}
	result['id'] = avaiTime.id
	result['startTime'] = datetime2timestamp(avaiTime.startTime.timestamp())
	result['endTime'] = datetime2timestamp(avaiTime.endTime.timestamp())
	return result
	
def rsrvProjectToDict(project, detail = False):
	result = {}
	result['id'] = project.id
	result['name'] = project.name
	result['haveToken'] = project.haveToken
	if detail:
		result['introduction'] = project.intro
	if project.contest:
		result['contest'] = project.contest.id
	return result
	
def teamToDict(team, detail = False):
	result = {'id': team.id, 'name': team.name, 'introduction': team.introduction, 'captain': team.captain.username, 'members': [], 'candidates': []}
	if detail:
		candidateList = team.candidates.all()
		for candidate in candidateList:
			result['candidates'].append(userToDict(candidate, True))
	
	memberList = team.members.all()
	for member in memberList:
		if not member==team.captain:
			result['members'].append(userToDict(member, detail))
	
	return result
	
def teamToJson(team, detail = False):
	return json.dumps(teamToDict(team, detail))
	
def blogToDict(blog):
	result = {}
	result['id'] = blog.id
	result['title'] = blog.title
	result['content'] = blog.content
	result['author'] = blog.author.username
	result['time'] = blog.timestamp.strftime('%Y-%m-%d %H:%M:%S')
	result['tags'] = []
	tags = blog.tags.all()
	for tag in tags:
		result['tags'].append(tag.name)
	return result

def problemToDict(problem, detail = True):
	result = {}
	result['id'] = problem.id
	result['title'] = problem.title
	result['author'] = problem.author.username
	result['time'] = problem.timestamp.strftime('%Y-%m-%d %H:%M:%S')
	if detail:
		result['content'] = problem.content
	return result
def submissionToDict(submission, detail = False):
	result = {}
	result['id'] = submission.id
	result['problem'] = {'id': submission.problem.id, 'title': submission.problem.title}
	result['user'] = submission.user.username
	result['date'] = submission.timestamp.strftime('%Y-%m-%d %H:%M:%S')
	result['time'] = submission.timeUsed
	result['score'] = submission.score
	result['status'] = submission.status
	if detail:
		result['code'] = 'media/' + str(submission.code)
	return result


def getTeamByUsernameContestid(username, contestID):
	return User.objects.get(username = username).belong.filter(contest__id = contestID)
def getTeamByUserContest(user, contest):
	team = user.belong.filter(contest = contest)
	if len(team) == 0:
		return None
	else:
		return team[0]
def updateHighestScore(submission, inContest = False):
	if (submission.score < 0):
		return
	if (inContest):
		record = ProblemHighestScore.objects.filter(team = submission.team, problem = submission.problem)
	else:
		record = ProblemHighestScore.objects.filter(user = submission.user, team__isnull = True, problem = submission.problem)

	if (record.count() == 0):
		team = None
		if (inContest):
			team = submission.team
		
		ProblemHighestScore(user = submission.user, problem = submission.problem, team = team, submission = submission).save()
	elif (record[0].submission.score < submission.score):
		s = record[0]
		s.submission = submission
		s.save()

def getSubmissionScore(submission):
	if (submission.problem.timestamp < datetime.datetime.now()):
		return submission.score
	else:
		return 0

def getHighestScoreByContest(contest):
	records = ProblemHighestScore.objects.none()
	for problem in contest.problems.all():
		records = records | problem.highestScore.filter(team__isnull = False).order_by('team__id').all()
	return records

def getSubmissionByContest(contest):
	records = ProblemSubmission.objects.none()
	for problem in contest.problems.all():
		records = records | problem.submissions.filter(team__isnull = False).order_by('team__id').all()
	return records