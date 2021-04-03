import os
import argparse
import subprocess

def compile(code, program):
	codeType = code.split('/')[-1].split('.')[-1]
	if codeType == 'zip':
		codeType = 'make'
	Compile = subprocess.Popen('./'+codeType+'.sh ' + code + ' ' + program, shell=True, cwd='/compile', stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	try:
		out, err = Compile.communicate(timeout=20)
	except subprocess.TimeoutExpired:
		Compile.terminate()
		result = ' '.join(['0', 'CompileTimeout'])
	else:
		if Compile.returncode:
			result = ' '.join(['0', 'CompileError'])
		else:
			result = ' '.join(['1', 'Successful'])
	return result

def problemJudge(id, program):
	path = os.path.join('/data', '%04d'%(int(id)))
	result = subprocess.run(['python3', 'judge.py', '-ai', program], encoding='utf-8', cwd=path, stdout=subprocess.PIPE, stderr=subprocess.PIPE).stdout
	return result

def gameJudge(id, program, record):
	path = os.path.join('/game', '%04d'%(int(id)))
	result = subprocess.run(['python3', 'judge.py', '-ai'] + program, encoding='utf-8', cwd=path, stdout=subprocess.PIPE, stderr=subprocess.PIPE).stdout
	if os.path.exists(os.path.join(path, 'record.zip')) and record:
		subprocess.run(['cp', os.path.join(path, 'record.zip'), record])
	return result

if __name__ == "__main__":
	parser = argparse.ArgumentParser(description="")
	parser.add_argument('-j', '--judge', help="judge type('game' or 'problem' or 'complie')")
	parser.add_argument('-c', '--code', help="code path", default='')
	parser.add_argument('-r', '--record', help="record path", default='')
	parser.add_argument('-p', '--program', nargs='*', help="program path")
	parser.add_argument('-id', '--id', help="problem ID or game ID", default='0')
	args=parser.parse_args()

	if args.judge == 'compile':
		print(compile(args.code, args.program[0]))
	elif args.judge == 'problem':
		print(problemJudge(args.id, args.program[0]))
	elif args.judge == 'game':
		print(gameJudge(args.id, args.program, args.record))
