import time
import random
import argparse
import threading
import subprocess
import numpy as np

Width = 20
Height = 20
BlockSize = 30
WaitTime = 10
PlayerNumber = 2
BlockNumber = 20
Range = 5
Play = True
Seed = int(time.time())
Game = './link.exe'
AIs = []
Blocks = []
TimeLimit = 1
Output = True




if __name__ == "__main__":
	parser = argparse.ArgumentParser(description="")
	parser.add_argument('-w', '-W', '--Width', default=Width, help='width of the game')
	parser.add_argument('-H', '--Height', default=Height, help='height of the game')
	parser.add_argument('-pn', '-PN', '--PlayerNumber', default=PlayerNumber, help='number of players')
	parser.add_argument('-bn', '-BN', '--BlockNumber', default=BlockNumber, help='number of blocks')
	parser.add_argument('-s', '-S', '--Seed', default=Seed, help='seed of random')
	parser.add_argument('-r', '-R', '--Range', default=Range, help='range')
	parser.add_argument('-p', '-Play', '--Play', action='store_true', help='show the process')
	parser.add_argument('-o', '-Output', '--Output', action='store_true', help='Output the details')
	parser.add_argument('-g', '-G', '--Game', default=Game, help='main game')
	parser.add_argument('-rp', '--replaypath', nargs='*', help='replay')
	parser.add_argument('-ai', '--ai', nargs='*', help="player's AI")
	args=parser.parse_args()
	
	Width = int(args.Width)
	Height = int(args.Height)
	PlayerNumber = int(args.PlayerNumber)
	BlockNumber = int(args.BlockNumber)
	Range = int(args.Range)
	Seed = int(args.Seed)
	if not args.Play:
		Play = False
	if not args.Output:
		Output = False
	Game = args.Game

	for i in range(PlayerNumber):
		if args.ai and len(args.ai)>i:
			AIs.append(args.ai[i])
		else:
			AIs.append('ai'+str(i)+'.exe')
			
	random.seed(Seed)
	
	for i in range(BlockNumber):
		Blocks.append([random.randint(0, Height-1), random.randint(0, Width-1)])


	GameInfo = str(Height)+' '+str(Width)+' '+str(PlayerNumber)+' '+str(BlockNumber)+' '+str(Range)+'\n'	
	for block in Blocks:
		GameInfo += str(block[0])+' '+str(block[1])+'\n'


	if Play:
		PlayNumber = 1
	else:
		PlayNumber = 0
	GamePro = subprocess.Popen(Game, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
	GamePro.stdin.write((str(PlayNumber)+' '+GameInfo).encode(encoding='utf-8'))
	GamePro.stdin.flush()
	
	AIpro = []
	for ai in AIs:
		AIpro.append(subprocess.Popen(ai, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE))
	for ai in AIpro:
		if ai.returncode is None:
			ai.stdin.write(GameInfo.encode(encoding='utf-8'))
			ai.stdin.flush()

	gameOver = False
	roundId = 0
	while(gameOver == False):
		if Output:
			print('\nRound ' + str(roundId))
			
		operaList = [-1 for i in range(PlayerNumber)]
		debugOutput = []
		def player(id):
			if AIpro[id].poll() is not None:
				return
			try:
				output = AIpro[id].stdout.readline().decode('utf-8')
				tmp = output.split(' ')
				debugOutput.append(AIpro[id].stdout.readline().strip())
				if len(tmp)>0:
					operaList[id] = int(tmp[0])
			except:
				pass
		
		for i in range(PlayerNumber):
			th = threading.Thread(target=player, args=(i,))
			th.start()
			th.join(timeout=TimeLimit)

		if Output:
			print("AIs' output", operaList)
			print('Debug output', debugOutput)

		for i in range(PlayerNumber):
			GamePro.stdin.write((str(operaList[i])+' ').encode(encoding='utf-8'))
			for j in range(PlayerNumber):
				if i!=j and AIpro[i].poll() is None:
					try:
						AIpro[i].stdin.write((str(operaList[j])+' ').encode(encoding='utf-8'))
						AIpro[i].stdin.flush()
					except:
						pass
		GamePro.stdin.flush()
		#time.sleep(1)
		gameOver = GamePro.stdout.readline().decode('utf-8')[0] == '1'


		
		def showGameDetail():
			score = GamePro.stdout.readline().decode('utf-8').strip().split(' ')
			gameField = []
			for i in range(Height):
				gameField.append(GamePro.stdout.readline().decode('utf-8').strip().split(' '))
				print(gameField[-1])
			print('score:', score)

			colors = [[211, 211, 211], [0, 0, 0], [255, 0, 0], [0, 255, 0], [0, 0, 255], [0, 255, 255]]
			import cv2
			size = BlockSize
			img = np.zeros((Height*size, Width*size, 3),dtype=np.uint8)
			for i in range(Height * size):
				for j in range(Width * size):
					c=(colors[int(gameField[i//size][j//size])+2])
					img[Height*size - 1 - i, j, :]=c
			cv2.imshow('Link',img)
			cv2.waitKey(WaitTime)

		
		if Play == 1:
			showGameDetail()
		
		roundId += 1

	score = GamePro.stdout.readline().decode('utf-8').strip().split(' ')
	print(' '.join([str(x) for x in score]))
	GamePro.terminate()
	for ai in AIpro:
		ai.terminate()
