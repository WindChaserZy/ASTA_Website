#include "ai.h"
//#include <random>
//#include <iostream>
//#include <time.h>
//#define DEBUG
//#define SETSEED
/*			普僵	(270)	铁桶(550+270)	撑杆跳(200)	雪橇车(1600)	伽刚特尔(3000)
向日葵(300)	-/3.6		-/3.6			-/3.6		-/1			-/1
豌豆(300)	28/3.6		82/3.6			20/3.6		160/1		300/1
冰豌豆(300)	15/3.6		41/3.6			10/3.6		80/1		150/1
辣椒	(300)	1/-			1/-				1/			1/1			2/1
倭瓜	(300)	1/-			1/-				1/			1/1			2/1
坚果墙(4000)	-/53.3		-/53.3			-/53.3		-/1			-/1

坚果摆在哪一列？4
向日葵种植数量？4
何时种植冰豌豆？

开局种4个

普僵：在左侧放置豌豆
铁桶：在第4格放坚果
撑杆：在撑杆所在的格子放置向日葵
雪橇车：如果有倭瓜在其前一格放倭瓜，如没有则放置辣椒
伽刚特尔：在其所在格放置倭瓜和辣椒（优先级高于雪橇车）


冷却时间主要按月光考虑，次要按CD计算

*/
//enum PlantType {
//	NOPLANT = 0,
//	SUNFLOWER,
//	WINTERPEASHOOTER,
//	PEASHOOTER,
//	SMALLNUT,
//	PEPPER,
//	SQUASH
//};
//enum ZombieType {
//	NOZOMBIE = 0,
//	NORMAL,
//	BUCKET,
//	POLEVAULT,
//	SLED,
//	GARGANTUAR
//};
//enum TryPlant {
//	SUCCEED = 0,
//	WAITCD,
//	NOSPACE,
//	INVALIDTYPE
//};
//using namespace std;
//const int PlantSun[6] = { 50, 100, 400, 125, 50, 50 };
//const int ZombieSun[5] = { 50, 125, 125, 300, 300 };
//int TryPlacePlant(IPlayer *const player, int PlantType, int x, int y);
//选手代码在下方填入
void player_ai(IPlayer *player) {
//	//both
//	int CampType = player->Camp->getCurrentType();
//	static bool isInitalized = false;
//	const int Rows = player->Camp->getRows();
//	const int Columns = player->Camp->getColumns();
//	if (CampType == 0) {
//		//Plants
//		/*
//		需要解决的问题：
//		根据重要程度决策。例如离底线较近的僵尸需要优先考虑，防御较少的行优先考虑。
//		寒冰射手。大后期需要用来拖慢速度。
//		阳光冗余。阳光堆积太多，可以适当种一些豌豆。
//		*/
//
//		int ***Zombies = player->Camp->getCurrentZombies();
//		int **Plants = player->Camp->getCurrentPlants();
//		int *PlantsCD = player->Camp->getPlantCD();
//		bool isGiant = false;
//		bool isSled = false;
//		for (int i = 0; i < Rows; i++)
//			for (int j = 0; j < Columns; j++)
//				for (int k = 0; k < 2 && Zombies[i][j][k] != -1; k++) {
//					switch (Zombies[i][j][0])
//					{
//					case NORMAL:		//普僵
//						if (Plants[i][1] == NOPLANT) {
//							player->PlacePlant(PEASHOOTER, i, 1);
//						}
//						break;
//					case BUCKET:		//铁桶
//						if (Plants[i][1] == NOPLANT) {
//							if (TryPlacePlant(player, SQUASH, i, j) == WAITCD) {
//								player->PlacePlant(PEASHOOTER, i, 1);
//							}
//						}
//						else if (Plants[i][2] == NOPLANT) {
//							player->PlacePlant(PEASHOOTER, i, 2);
//						}
//						else if (Plants[i][5] == NOPLANT) {
//							player->PlacePlant(SMALLNUT, i, 5);
//						}
//						else if (Plants[i][3] == NOPLANT) {
//							player->PlacePlant(PEASHOOTER, i, 3);
//						}
//
//						break;
//					case POLEVAULT:		//撑杆
//						if (Plants[i][1] == NOPLANT) {
//							player->PlacePlant(PEASHOOTER, i, 1);
//						}
//						if (TryPlacePlant(player, SUNFLOWER, i, j) == WAITCD) {
//							if (TryPlacePlant(player, SMALLNUT, i, j) == WAITCD) {
//								TryPlacePlant(player, PEASHOOTER, i, 2);
//							}
//						}
//						break;
//					case SLED:		//雪橇车
//						if (TryPlacePlant(player, SQUASH, i, j) == SUCCEED) {
//
//						}
//						else
//						{
//							TryPlacePlant(player, PEPPER, i, j);
//						}
//						break;
//					case GARGANTUAR:		//伽刚特尔
//						TryPlacePlant(player, SQUASH, i, j);
//						TryPlacePlant(player, PEPPER, i, j);
//						break;
//					default:
//						break;
//					}
//				}
//		//种植4个向日葵
//		int i;
//		for (i = 0; i < 4 && Plants[i][0] != NOPLANT; i++);
//		player->PlacePlant(SUNFLOWER, i, 0);
//		if (player->getTime() >= 250 && Plants[4][0] == NOPLANT) {
//			if (Plants[4][1] == NOPLANT)
//				player->PlacePlant(SUNFLOWER, 4, 0);
//		}
//		//}
//	}
//
//	if (CampType == 1) {
//		//Zombie
//		static int *ZombieTypes;
//		static int *lines;
//		static int ZombieIndex = 0;
//		static int LineIndex = 0;
//		if (!isInitalized) {
//			ZombieIndex = 0;
//			LineIndex = 0;
//			ZombieTypes = new int[2000];
//			lines = new int[2000];
//			time_t t;
//			unsigned int seed = (unsigned)time(&t);
//			srand(seed); //1650425929
//			isInitalized = true;
//#ifdef SETSEED
//			cout << "Initialized! seed: " << seed << endl;
//#endif // DEBUG
//
//			for (int i = 0; i < 2000; i++) {
//				ZombieTypes[i] = rand() % 5;
//				lines[i] = rand() % 5;
//			}
//		}
//		/*随机化策略：
//			随机生成僵尸，用于训练和调试植物
//			具体内容：随机抽取僵尸种类，若可以放置则放置，若不能放置，则等待放置条件成立后再放置
//			如果找到符合条件的，则抽取行数，并放置僵尸。
//		*/
//		int *ZombieCD = player->Camp->getPlantCD();
//		int ZombieType = 0;
//		int line = 0;
//			if (ZombieTypes != NULL) {
//				ZombieType = ZombieTypes[ZombieIndex];
//			}
//			else {
//#ifdef DEBUG
//
//				cout << "ZombieTypes is NULL! " << endl;
//#endif // DEBUG
//			}
//
//		if (lines != NULL) {
//			line = lines[LineIndex];
//		}
//		else
//		{
//#ifdef DEBUG
//
//			cout << "lines is NULL" << endl;
//#endif // DEBUG
//		}
//#ifdef DEBUG
//		cout << "index: " << LineIndex << endl;
//		cout << "Zombie Type: " << ZombieType << endl;
//		cout << "line: " << line << endl;
//		cout << "Sun:" << player->Camp->getSun() << endl;
//#endif // DEBUG
//		if (player->Camp->getSun() > ZombieSun[ZombieType]) {
//			int i;
//			for (i = 0; i < 5 && ZombieCD[(ZombieType + i) % 5] > 0; i++);
//			if (i<5) {
//				if (player->Camp->getLeftLines()[line]) {
//					player->PlaceZombie((ZombieType+ i)% 5  + 1, line);
//					ZombieIndex++;
//#ifdef DEBUG
//
//					cout << "Place Zombie: " << (ZombieType + i) % 5 + 1 << endl;
//#endif // DEBUG
//
//				}
//				else {
//#ifdef DEBUG
//
//					cout << "The line has been destroyed! line: " << line << endl;
//#endif // DEBUG
//				}
//				}
//			else {
//#ifdef DEBUG
//
//				cout << "The zombie is not cooled down! CD: " << ZombieCD[ZombieType] << endl;
//#endif // DEBUG
//				
//			}
//			}
//		else {
//#ifdef DEBUG
//
//			cout << "Sun is not enough! Sun needed: " << ZombieSun[ZombieType] << endl;
//#endif // DEBUG
//		}
//		LineIndex++;
//		if (LineIndex == 2000) {
//#ifdef DEBUG
//			cout << "random is ended!" << endl;
//#endif
//			delete[] ZombieTypes;
//			delete[] lines;
//			ZombieTypes = NULL;
//			lines = NULL;
//			ZombieIndex = 0;
//			LineIndex = 0;
//			isInitalized = false;
//		}
//	}
}
//返回三种状态，
//int TryPlacePlant(IPlayer *const player, int PlantType, int x, int y) {
//	if (PlantType < 1) {
//#ifdef DEBUG
//		cout << "Invalid PlantType! " << endl;
//#endif // DEBUG
//		return INVALIDTYPE;
//	}
//	if (player->Camp->getPlantCD()[PlantType - 1] > 0) {
//		return WAITCD;
//	}
//	if (player->Camp->getCurrentPlants()[x][y] != NOPLANT) {
//		return NOSPACE;
//	}
//	else
//	{
//		player->PlacePlant(PlantType, x, y);
//		return SUCCEED;
//	}
//
//}