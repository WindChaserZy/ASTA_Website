from database.models import User, Problem, ProblemSubmission
from celery import task, platforms
import os
import tarfile
import subprocess
from api import tools
from api.settings import BASE_DIR
platforms.C_FORCE_ROOT = True

@task
def problemJudge(submission):
    submission.status = "Judging"
    submission.save()

    path = os.path.join(BASE_DIR, 'judge/data', '%04d'%(submission.problem.id), 'program')
    Compile = subprocess.run(['g++', submission.code.path, '-o', path])
    if (Compile.returncode):
        submission.status = "Compile Error"
        submission.save()
        return
    result = subprocess.run(['python3', 'judge.py', '-ai', 'program'], encoding='utf-8', cwd=os.path.join(BASE_DIR, 'judge/data', '%04d'%(submission.problem.id)), stdout=subprocess.PIPE).stdout.split()
    submission.status = result[0]
    submission.score = float(result[1])
    submission.timeUsed = float(result[2])
    submission.save()

    tools.updateHighestScore(submission)
    if (submission.team):
        tools.updateHighestScore(submission, True)
    
    


