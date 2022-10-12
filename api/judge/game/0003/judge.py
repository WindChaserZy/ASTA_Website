import subprocess
import argparse
import json
import sys

if __name__ == "__main__":
	parser = argparse.ArgumentParser(description="")
	parser.add_argument('-ai', '--ai', nargs='*', help="player's AI", default=['./ai0.exe', './ai1.exe'])
	parser.add_argument('--judge', default='./judge.exe')
	args=parser.parse_args()
	
	subprocess.run(['rm -f record/round1/*'], shell=True)
	
	playerNumber = len(args.ai)
	JudgeProcess = subprocess.Popen(args.judge, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, encoding="utf-8")

	input2judge = ''
	errorLog = open("error.log", "w")
	while(JudgeProcess.returncode is None):
		JudgeProcess.stdin.write(input2judge + '\n')
		JudgeProcess.stdin.flush()
		playerInfo = JudgeProcess.stdout.readline()
		if playerInfo.count(' ') == playerNumber:
			score = [int(x) for x in playerInfo.split()]
			print(' '.join([str(x) if x>0 else '0' for x in score]))
			break
		playerID = int(playerInfo)
		infoData = JudgeProcess.stdout.readline()
		info = json.loads(infoData)

		input2judge = "[]"
		try:
			AIProcess = subprocess.Popen(args.ai[playerID], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, encoding="utf-8")
		except Exception:
			print('Player %d Error at Round %d'%(playerID, info["Player"]["getTime"]), file=errorLog)
			AIProcess.kill()
			continue


		try:
			aiOut, aiErr = AIProcess.communicate(infoData, timeout=0.1)
			if aiErr:
				print('Player %d Error at Round %d'%(playerID, info["Player"]["getTime"]), file=errorLog)
				print('aiError\n', aiErr, file=errorLog)
		except subprocess.TimeoutExpired:
			print('Player %d Timeout at Round %d'%(playerID, info["Player"]["getTime"]), file=errorLog)
		except Exception:
			print(Exception, file=errorLog)
		else:
			if (AIProcess.returncode == 0):
				input2judge = aiOut.split()[0]
		AIProcess.kill()
		#print(input2judge)
	
	JudgeProcess.kill()
	errorLog.close()
	subprocess.run(['zip', '-qr', 'record.zip', 'record', 'error.log'])
