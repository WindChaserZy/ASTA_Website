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

    codePath = os.path.join(BASE_DIR, 'judge/code')
    filetype = submission.code.name.split('.')[-1]
    subprocess.run(['cp', submission.code.path, os.path.join(codePath, 'code.'+filetype)])
    if filetype == 'zip':
        compileType = 'make'
    else:
        compileType = filetype

    judge = subprocess.Popen([  'docker', 'run', '-m', '1g', '--memory-swap', '1g', '-v', codePath+':/code',\
                                'judge_box', '-p', str(submission.problem.id), '-t', compileType],\
                                encoding='utf-8', stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    try:
        judgeout, judgeerr = judge.communicate(timeout=60)
    except subprocess.TimeoutExpired:
        result = ['SystemTimeout', 0, 0]
    else:
        result = judgeout.split()
        
    subprocess.run(['rm', os.path.join(codePath, 'code.'+filetype)])

    submission.status = result[0]
    submission.score = float(result[1])
    submission.timeUsed = float(result[2])
    submission.save()

    tools.updateHighestScore(submission)
    if (submission.team):
        tools.updateHighestScore(submission, True)
