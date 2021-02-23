import subprocess
import argparse
import json
import sys

if __name__ == "__main__":
	parser = argparse.ArgumentParser(description="")
	parser.add_argument('-ai', '--ai', nargs='*', help="player's AI", default=['./ai0.exe', './ai1.exe', './ai2.exe', './ai3.exe'])
	parser.add_argument('--judge', default='./judge.exe')
	args=parser.parse_args()
	
	playerNumber = len(args.ai)
	JudgeProcess = subprocess.Popen(args.judge, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, encoding="utf-8")

	input2judge = ''
	while(JudgeProcess.returncode is None):
		JudgeProcess.stdin.write(input2judge + '\n')
		JudgeProcess.stdin.flush()
		playerInfo = JudgeProcess.stdout.readline()
		if playerInfo.count(' ') == playerNumber:
			#print(playerInfo)
			playerScore = [0] * playerNumber
			rank = playerInfo.split(' ')
			for i in range(len(rank)):
				try:
					playerScore[int(rank[i])] = playerNumber - i
				except:
					pass
			print(' '.join(str(x) for x in playerScore))
			break
		playerID = int(playerInfo)
		#print(playerID)
		infoData = JudgeProcess.stdout.readline()
		info = json.loads(infoData)
		#print("Round", info["totalRounds"])

		AIProcess = subprocess.Popen(args.ai[playerID], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, encoding="utf-8")


		input2judge = "[]"
		try:
			aiOut, aiErr = AIProcess.communicate(infoData, timeout=0.5)
		except subprocess.TimeoutExpired:
			print('Player %d Timeout'%playerID)
		except Exception:
			print(Exception)
		else:
			if (AIProcess.returncode == 0):
				input2judge = aiOut.split()[0]
		#print(input2judge)