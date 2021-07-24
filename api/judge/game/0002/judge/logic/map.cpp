//#2021-1-19 <JYP> 熟悉代码，添加注释
//#2021-1-28 <JYP> checked，检查代码，更改错误
#include"map.h"
#include<fstream>
#include<iostream>
#include "data.h"
#include "Crops.h"
#include "tower.h"
#include "player.h"
#include <cstdio>
#include <utility>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using std::pair;
using std::vector;
using std::set;
using std::sprintf;
using std::sscanf;

TPoint TRClassRoomFill[4][11] =
{
{{1,0},{2,0},{3,0},{0,1},{1,1},{2,1},{3,1},{0,2},{1,2},{0,3},{1,3}},
{{-1,0},{-2,0},{-3,0},{0,1},{-1,1},{-2,1},{-3,1},{0,2},{-1,2},{0,3},{-1,3}},
{{-1,0},{-2,0},{-3,0},{0,-1},{-1,-1},{-2,-1},{-3,-1},{0,-2},{-1,-2},{0,-3},{-1,-3}},
{{1,0},{2,0},{3,0},{0,-1},{1,-1},{2,-1},{3,-1},{0,-2},{1,-2},{0,-3},{1,-3}}
};


/***********************************************************************************************
*函数名 :【FC18】readMap读入地图函数
*函数功能描述 : 通过文件读入当前游戏的地图数据、玩家数量数据，并初始化玩家数组，写入零回合命令
                Json
*函数参数 : inMap<ifstream&> 输入文件流对象，enableOutput<bool> 是否输出调试信息（true--允许，
            false--不允许）
*函数返回值 : false--读入地图失败，true--读入地图成功
*作者 : 姜永鹏
***********************************************************************************************/
bool Map::readMap(ifstream& inMap, ofstream& cmdF,ofstream& infoF, bool enableOutput, std::vector<std::string> players_name, string log_path) {
	this->log_path = log_path;
	data->resetAllCnt();             //初始化过程为第0回合
	//初始化地图高度、宽度
	if (enableOutput)
#ifdef NOTICE
		cout << "init map......" << endl;
#endif // NOTICE
	inMap >> m_height;
	inMap >> m_width;
	//data->mapInfoJsonRoot["head"]["height"] = Json::Value(std::to_string(m_height));
	//data->mapInfoJsonRoot["head"]["width"] = Json::Value(std::to_string(m_width));


	//rankInfo
	//更新当前回合的排名信息JSON，不知道第5名无名氏玩家为什么也在Json里，但是暂时照着FC15原码修改了
	/*Json::Value rankInfoJson;
	Json::Value rankUnit;
	for (int i = 1; i < 5; i++) {
		rankUnit["rk"] = Json::Value(std::to_string(i));
		rankUnit["scr"] = Json::Value(std::to_string(1 * TOWER_SCORE));
		rankInfoJson.append(rankUnit);
	}
	rankUnit["rk"] = Json::Value(std::to_string(0));
	rankUnit["scr"] = Json::Value(std::to_string(-INF));
	rankInfoJson.append(rankUnit);
	data->currentRoundPlayerJson["rankInfo"] = rankInfoJson;*/


	//初始化阵营
	if (enableOutput)
#ifdef NOTICE
		cout << "init team......" << endl;
#endif // NOTICE

	inMap >> data->totalPlayers;
	//data->commandJsonRoot["head"]["totalPlayers"] = Json::Value(std::to_string(data->totalPlayers)); //#json
	data->players = new Player[data->totalPlayers];




	/*for (int i = 1; i < 5; i++) {
		Json::Value playerJson;
		playerJson["id"] = Json::Value(std::to_string(i));
		playerJson["team"] = Json::Value(std::to_string(i));
		playerJson["name"] = Json::Value(players_name[i]);
		data->commandJsonRoot["head"]["playerInfo"].append(playerJson);
	}*/


	//#json add
	//初始化玩家信息JSON
	//初始化玩家操作JSON
	//Json::Value playerActionJson; 
	for (int i = 0; i < data->totalPlayers; ++i)
	{
		data->players[i].setdata(data);
		data->players[i].setID(i + 1);
		data->players[i].setName(players_name[i]);
		/*Json::Value playerJson;
		playerJson["id"] = Json::Value(std::to_string(i + 1));
		playerJson["nm"] = Json::Value(players_name[i]);
		playerJson["cpN"] = Json::Value(std::to_string(0));
		playerJson["twN"] = Json::Value(std::to_string(1));
		playerJson["scr"] = Json::Value(std::to_string(1 * TOWER_SCORE));
		playerJson["rk"] = Json::Value(std::to_string(i + 1));
		data->currentRoundPlayerJson.append(playerJson);*/

		/*Json::Value paj;
		paj["oId"] = Json::Value(std::to_string(i + 1));
		paj["tp"] = Json::Value(std::to_string(-1));
		paj["id"] = Json::Value(std::to_string(-1));
		paj["x"] = Json::Value(std::to_string(-1));
		paj["z"] = Json::Value(std::to_string(-1));
		paj["rst"] = Json::Value(std::to_string(0));
		paj["dT"] = Json::Value(std::to_string(-1));
		paj["pT"] = Json::Value(std::to_string(-1));
		paj["aid"] = Json::Value(std::to_string(-1));
		data->currentRoundCommandJson["command"].append(paj);*/
	}


	//初始化兵团的表
	/*data->corps = new CorpsUnit*[m_height];
	for (int i = 0; i < m_height; i++) {
		data->corps[i] = new CorpsUnit[m_width];
	}*/
#ifdef SAVETXT
	char bufferCorps[64];
	sprintf(bufferCorps, "#corps\n");
	infoF << bufferCorps;
#endif // !SAVETXT
	return true;
}

/***********************************************************************************************
*函数名 :【FC18】randomInitMap随机地图产生器
*函数功能描述 : 初始化确定地图长、宽之后，为每个地图方格分配地形，划分各势力的初始领土，分配塔
                的初始位置
*函数参数 : 无
*函数返回值 : false--随机地图初始化失败，true--随机地图初始化成功
*作者 : 姜永鹏
***********************************************************************************************/
bool Map::randomInitMap(ofstream& cmdFile,ofstream& infoFile) {
	int Xinterval, Yinterval;         //X方向和Y方向地图的公共区域条带宽度
	Xinterval = (m_width % 2 == 0) ? 2 : 3;
	Yinterval = (m_height % 2 == 0) ? 2 : 3;
	for (int i = 0; i < m_height; i++) {
		vector<mapBlock> newVectorMapBlock;
		map.push_back(newVectorMapBlock);
		for (int j = 0; j < m_width; j++) {
			mapBlock newBlock;               //地块初始化，无塔，平原，没有主人，占有属性值为0
			newBlock.TowerIndex = NOTOWER;
			newBlock.owner = PUBLIC;
			newBlock.type = TRPlain;
			for (int k = 0; k < 4; k++) {
				newBlock.occupyPoint.push_back(0);    //各方格初始占有属性值均为0
			}
			map[i].push_back(newBlock);
		}
	}
	vector<pair<TPoint, TPoint>> towerRegion;         //各玩家生成随机防御塔的位置范围
	towerRegion.resize(4);


	if (data->gameState == Normal) {
		//【FC18】利用柏林噪声方法产生随机地图
		Perlin perlinNoiseGen;
		int terrainArea[TERRAIN_TYPE_NUM] = { 0 };      //【FC18】统计每种地形生成了多少格
		double** perlinNoise = new double* [m_height];  //【FC18】柏林噪声表
		for (int i = 0; i < m_height; i++) {
			perlinNoise[i] = new double[m_width];
		}
		int** typeOfTerrain = new int* [m_height];      //【FC18】地形预分配表
		for (int i = 0; i < m_height; i++) {
			typeOfTerrain[i] = new int[m_width];
		}

		double minNoise = INF, maxNoise = -INF;
		for (int i = 0; i < m_height; i++) {             //生成柏林噪声表，并记录其中的最大、最小噪声值
			for (int j = 0; j < m_width; j++) {
				typeOfTerrain[i][j] = UNALLOCATED;       //初始化所有格地形均为未分配
				perlinNoise[i][j] = perlinNoiseGen.PerlinNoise(i, j);            //生成初始的柏林噪声
				if (perlinNoise[i][j] > maxNoise) maxNoise = perlinNoise[i][j];
				if (perlinNoise[i][j] < minNoise) minNoise = perlinNoise[i][j];
			}
		}
		double interval = (maxNoise - minNoise) / TERRAIN_TYPE_NUM;
		for (int i = 0; i < m_height; i++) {
			for (int j = 0; j < m_width; j++) {
				for (int k = 0; k < TERRAIN_TYPE_NUM; k++) {
					if (((perlinNoise[i][j] - minNoise) >= k * interval) && ((perlinNoise[i][j] - minNoise) < (k + 1) * interval)) {
						typeOfTerrain[i][j] = k;
						break;
					}
				}
				if (typeOfTerrain[i][j] == UNALLOCATED) typeOfTerrain[i][j] = TERRAIN_TYPE_NUM - 1;
			}
		}
		for (int itercnt = 0; itercnt < perlinNoiseGen.iterRound; itercnt++) {
			for (int i = 1; i < m_height - 1; i++) {
				for (int j = 1; j < m_width - 1; j++) {
					int nums[TERRAIN_TYPE_NUM] = { 0 };
					for (int k = 0; k < 8; k++) {
						int newPosX = j + paraOffset[k].m_x;
						int newPosY = i + paraOffset[k].m_y;
						int scaleValue = typeOfTerrain[newPosY][newPosX];
						nums[scaleValue]++;
					}
					for (int cnt = 0; cnt < TERRAIN_TYPE_NUM; cnt++) {
						if (nums[cnt] >= perlinNoiseGen.connectStandard) typeOfTerrain[i][j] = cnt;
					}
					if (itercnt == perlinNoiseGen.iterRound - 1) {
						int currentType = typeOfTerrain[i][j];
						terrainArea[currentType]++;
					}
				}
			}
		}
		vector<pair<int, int>> areaRankPair;
		for (int i = 0; i < TERRAIN_TYPE_NUM; i++) {
			areaRankPair.push_back({ i,terrainArea[i] });
		}
		std::sort(areaRankPair.begin(), areaRankPair.end(),
			[](const pair<int, int>& a, pair<int, int>& b) {return a.second > b.second; });
		std::map<int, int> areaRankMap;
		for (int i = 0; i < TERRAIN_TYPE_NUM; i++) {
			areaRankMap.insert(pair<int, int>(areaRankPair[i].first, i));
		}
		for (int i = 0; i < m_height; i++) {      //生成地形
			for (int j = 0; j < m_width; j++) {
				int type = typeOfTerrain[i][j];
				int rank;
				if (areaRankMap.count(type) > 0)
					rank = areaRankMap[type];
				else
					rank = 0;
				map[i][j].type = terrain[rank];
			}
		}
		for (int i = 0; i < m_height; i++) {
			delete[] perlinNoise[i];
			delete[] typeOfTerrain[i];
		}
		delete[] perlinNoise;
		delete[] typeOfTerrain;

		////////////////////////////////////////////////////////
		//【FC18】分配各势力的初始领土，占据方形地图的四个角落//
		//地图的样子                                          //
		//      X(i=0)--------m_width---------                //
		//Y(j=0)         0     PUB      1                     //
		//  |           PUB    PUB     PUB                    //
		//  |            3     PUB      2                     //
		////////////////////////////////////////////////////////
		for (int j = 0; j < m_height; j++) {
			for (int i = 0; i < m_width; i++) {
				if ((i < ((m_width - Xinterval) / 2)) && (j < ((m_height - Yinterval) / 2))) map[j][i].owner = 1;
				else if ((i > ((m_width + Xinterval) / 2) - 1) && (j < ((m_height - Yinterval) / 2))) map[j][i].owner = 2;
				else if ((i > ((m_width + Xinterval) / 2) - 1) && (j > ((m_height + Yinterval) / 2) - 1)) map[j][i].owner = 3;
				else if ((i < ((m_width - Xinterval) / 2)) && (j > ((m_height + Yinterval) / 2 - 1))) map[j][i].owner = 4;
				else map[j][i].owner = PUBLIC;
			}
		}
		////////////////////////////////////////////////////////
		//【FC18】给清华元素地形安排位置                      //
		////////////////////////////////////////////////////////
		//为清华学堂随机生成位置
		int direction = generateRanInt(7 + 1, 7 + 4);
		int ori_posx = ceil((m_width - 1) / 2.0);
		int ori_posy = ceil((m_height - 1) / 2.0);
		map[ori_posy][ori_posx].type = (enum terrainType)(direction);
		for (int i = 0; i < 11; i++) {
			int posx = ori_posx + TRClassRoomFill[direction - 8][i].m_x;
			int posy = ori_posy + TRClassRoomFill[direction - 8][i].m_y;
			map[posy][posx].type = TRTHUEmpty;
		}
		//给大礼堂和二校门随机安排位置
		enum terrainType THUelems[2] = { TRGate, TRHall };
		for (int i = 0; i < 2; i++) {
			enum direction{XRand = 0, ZRand = 1};
			int direction = generateRanInt(0, 1);  //0：在x方向随机，1：在z方向随机
			set<enum terrainType> THUelemList = {TRGate, TRHall, TRClassRoom1, TRClassRoom2, TRClassRoom3, TRClassRoom4, TRTHUEmpty};
			if (direction == XRand) {
				bool invalidPos = true;
				int posx = 0, posz = 0;
				while (invalidPos) {
					invalidPos = false;
					posx = generateRanInt(0, m_width - 2);
					posz = generateRanInt(ceil((m_height - 1) / 2.0) - ceil(Yinterval / 2.0) + 1, ceil((m_height - 1) / 2.0));
					for (int dx = 0; dx < 2; dx++) {
						for (int dz = 0; dz < 2; dz++) {
							if (THUelemList.find(map[posz + dz][posx + dx].type) != THUelemList.end())
								invalidPos = true;
						}
					}
				}
				for (int dx = 0; dx < 2; dx++) {
					for (int dz = 0; dz < 2; dz++) {
						if (dx == 0 && dz == 0)
							map[posz + dz][posx + dx].type = THUelems[i];
						else
							map[posz + dz][posx + dx].type = TRTHUEmpty;
					}
				}
			}
			else if (direction == ZRand) {
				bool invalidPos = true;
				int posx = 0, posz = 0;
				while (invalidPos) {
					invalidPos = false;
					posx = generateRanInt(ceil((m_width - 1) / 2.0) - ceil(Xinterval / 2.0) + 1, ceil((m_width - 1) / 2.0));
					posz = generateRanInt(0, m_height - 2);
					for (int dx = 0; dx < 2; dx++) {
						for (int dz = 0; dz < 2; dz++) {
							if (THUelemList.find(map[posz + dz][posx + dx].type) != THUelemList.end())
								invalidPos = true;
						}
					}
				}
				for (int dx = 0; dx < 2; dx++) {
					for (int dz = 0; dz < 2; dz++) {
						if (dx == 0 && dz == 0)
							map[posz + dz][posx + dx].type = THUelems[i];
						else
							map[posz + dz][posx + dx].type = TRTHUEmpty;
					}
				}
			}
		}
		/*int mode = generateRanInt(0, 3);
		TPoint startPoint;
		if (mode == 0 || mode == 1) {
			startPoint.m_x = generateRanInt(0, m_width - 4);
			startPoint.m_y = (m_height - 1) / 2 - 1;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 4; j++) {
					switch (mode) {
					case(0):
						map[startPoint.m_y + i][startPoint.m_x + j].type = attachTerrain0[i][j];
						break;
					case(1):
						map[startPoint.m_y + i][startPoint.m_x + j].type = attachTerrain1[i][j];
						break;
					default:;
					}
				}
			}
		}
		else if (mode == 2 || mode == 3) {
			startPoint.m_x = (m_width - 1) / 2 - 1;
			startPoint.m_y = generateRanInt(0, m_height - 4);
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 3; j++) {
					switch (mode) {
					case(2):
						map[startPoint.m_y + i][startPoint.m_x + j].type = attachTerrain2[i][j];
						break;
					case(3):
						map[startPoint.m_y + i][startPoint.m_x + j].type = attachTerrain3[i][j];
						break;
					default:;
					}
				}
			}
		}*/
	}

	else if (data->gameState == RecoverMap || data->gameState == RecoverRound) {
		if (!recoverFromMap(towerRegion)) return false;
	}

	////////////////////////////////////////////////////////
	//【FC18】为每个势力生成防御塔                        //
	//随机防御塔：每个势力的初始领地中随机生成一个防御塔  //
	//每个防御塔周围的8格设置为道路Road                   //
	//保证初始各势力的随机防御塔攻击范围不会覆盖到对方    //
	////////////////////////////////////////////////////////
	data->totalTowers = 0;
	if (((m_width - Xinterval) < 3 * 2) || ((m_height - Yinterval) < 3 * 2)) {      //判断是否有空间生成防御塔，如果有空间，则每个势力的最初领地至少是3 * 3的方格
#ifdef NOTICE
		cout << "map size: (" << m_width << "*" << m_height << ") too small!\n";
#endif
		return false;
	}


	//初始化塔及指令信息存档
#ifdef SAVETXT
	char bufferCmd[64];
	sprintf(bufferCmd, "#command\n");
	cmdFile << bufferCmd;
#endif // SAVETXT


	if (data->gameState == Normal) {
		towerRegion[0] = { {1,1},{(m_width - Xinterval) / 2 - 2,(m_height - Yinterval) / 2 - 2} };
		towerRegion[1] = { {(m_width + Xinterval) / 2 + 1,1},{m_width - 2,(m_height - Yinterval) / 2 - 2} };
		towerRegion[2] = { {(m_width + Xinterval) / 2 + 1,(m_height + Yinterval) / 2 + 1},{m_width - 2,m_height - 2} };
		towerRegion[3] = { {1,(m_height + Yinterval) / 2 + 1},{(m_width - Xinterval) / 2 - 2,m_height - 2} };
	}

	for (int i = 0; i < 4; i++) {
		TPoint towerPoint;
		towerPoint.m_x = generateRanInt(towerRegion[i].first.m_x, towerRegion[i].second.m_x);
		towerPoint.m_y = generateRanInt(towerRegion[i].first.m_y, towerRegion[i].second.m_y);
		//map[towerPoint.m_y][towerPoint.m_x].type = TRTower;  //重复 tower构造   //更新data的地图类：当前方格的地形修改为防御塔
		map[towerPoint.m_y][towerPoint.m_x].owner = i + 1;//重复 tower构造
		//map[towerPoint.m_y][towerPoint.m_x].TowerIndex = i;  //方格上的塔序号
		//重复 tower构造 data->totalTowers++;                      //更新data类：更新防御塔总数
		//@@@【FC18】[！！！这个塔的构造函数可能会改]更新data类：向防御塔向量中添加新增的防御塔
		Tower* newTower = new Tower(data, i + 1, towerPoint);
		data->myTowers.push_back(*newTower);
		//【FC18】更新player类：向player的防御塔序号向量中添加新的防御塔序号
		//重复 tower构造 data->players[i].getTower().insert(i);
		for (int j = 0; j < 8; j++) {  //规则：初始防御塔四周8格为道路
			TPoint p;
			p.m_x = towerPoint.m_x + paraOffset[j].m_x;
			p.m_y = towerPoint.m_y + paraOffset[j].m_y;
			//重复 tower构造 map[p.m_y][p.m_x].occupyPoint[i] = TowerOccupyPoint[0];
			map[p.m_y][p.m_x].type = TRRoad;
		}
		//写入txt存档
#ifdef SAVETXT
		char bufferCmd[128];
		sprintf(bufferCmd, "%d %d %d %d %d %d %d %d %d\n", i + 1, JBuild, -1, towerPoint.m_x, towerPoint.m_y, -1, -1, -1, -1);
		cmdFile << bufferCmd;
#endif // !SAVETXT
	}

	//塔信息存档
#ifdef SAVETXT
	char bufferTowerHead[64];
	sprintf(bufferTowerHead, "#tower\n");
	infoFile << bufferTowerHead;
	for (int i = 0; i < data->myTowers.size(); i++) {
		Tower newTower = data->myTowers[i];
		TPoint towerPoint = newTower.getPosition();
		char bufferTower[128];
		sprintf(bufferTower, "%d %d %d %d %d %d %d %d %d %d %d\n", i
			                                                     , towerPoint.m_x
			                                                     , towerPoint.m_y
			                                                     , newTower.getPlayerID()
			                                                     , newTower.getProductPoint()
			                                                     , NOTASK
			                                                     , -1
			                                                     , newTower.getHealthPoint()
			                                                     , newTower.getBattlePoint()
			                                                     , newTower.getLevel()
			                                                     , 1);
		infoFile << bufferTower;
	}
#endif
	////////////////////////////////////////////////////////
	//【FC18】每个势力防御塔向周边方格施加初始占有属性值  //
	////////////////////////////////////////////////////////
	/*重复，tower构造******
	for (int i = 0; i < data->myTowers.size(); i++) {
		TPoint towerPoint = data->myTowers[i].getPosition();
		modifyOccupyPoint(NOTOWER, data->myTowers[i].getOwnerID(), towerPoint);
	}
	***********************/
	/*for (int cnt = 0; cnt < 4; cnt++) {
		TPoint towerPoint = data->myTowers[cnt].getPosition();
		TPlayerID ownerID = data->myTowers[cnt].getOwnerID();
		for (int i = 0; i < m_height; i++) {
			for (int j = 0; j < m_width; j++) {
				TPoint currentPoint;
				currentPoint.m_x = j;
				currentPoint.m_y = i;
				TDist distance = getDist(currentPoint, towerPoint);
				if (distance >= 1 && distance <= 5)
					map[i][j].occupyPoint[ownerID - 1] += TowerOccupyPoint[distance - 1];
				else                     //在塔当前格内会getDist超过6，就不更新占有属性值了
					continue;
			}
		}
	}*/
	
	//int countRound = 0, countPlayer = 0;
#ifdef SAVETXT
	char bufferMap[64];
	sprintf(bufferMap, "#map\n");
	infoFile << bufferMap;
	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++) {
			char bufferBlock[64];
			int terrain = map[i][j].type;
			if (map[i][j].TowerIndex != NOTOWER) terrain = TRTower;
			sprintf(bufferBlock, "%d %d %d %d\n", j, i, terrain, map[i][j].owner);
			infoFile << bufferBlock;
			Json::Value blockJson;
			blockJson["x"] = Json::Value(j);
			blockJson["z"] = Json::Value(i);
			if (map[i][j].TowerIndex != NOTOWER)
				blockJson["tp"] = Json::Value(TRTower);
			else
				blockJson["tp"] = Json::Value(map[i][j].type);
			blockJson["oId"] = Json::Value(map[i][j].owner);
			data->currentRoundMapJson.append(blockJson);
			/*//Json::Value occupyPoint;  //暂不提供给Json
			//for (int k = 0; k < 4; k++) {
			//	Json::Value occupyPointUnit;
			//	occupyPointUnit["id"] = Json::Value(k + 1);
			//	occupyPointUnit["point"] = Json::Value(map[i][j].occupyPoint[k]);
			//	occupyPoint.append(occupyPointUnit);
			//}
			if (map[i][j].type == TRTower) {
				Json::Value towerJson;
				towerJson["id"] = Json::Value(std::to_string(map[i][j].TowerIndex));
				//Json::Value towerPos;
				towerJson["x"] = Json::Value(std::to_string(j));
				towerJson["z"] = Json::Value(std::to_string(i));
				//towerJson["pos"] = towerPos;
				towerJson["oId"] = Json::Value(std::to_string(map[i][j].owner));
				towerJson["pP"] = Json::Value(std::to_string(TowerInitConfig[0].initBuildPoint));
				Json::Value production;
				production["pT"] = Json::Value(std::to_string(NOTASK));
				production["pC"] = Json::Value(std::to_string(-1));
				towerJson["pdt"] = production;
				towerJson["hP"] = Json::Value(std::to_string(TowerInitConfig[0].initHealthPoint));
				towerJson["bP"] = Json::Value(std::to_string(TowerInitConfig[0].initProductPoint));
				towerJson["exp"] = Json::Value(std::to_string(0));
				towerJson["sL"] = Json::Value(std::to_string(1));
				towerJson["nT"] = Json::Value(std::to_string(1));
				data->currentRoundTowerJson.append(towerJson);
				Json::Value playerJson;
				playerJson["rk"] = playerJson["tm"] = playerJson["id"] = Json::Value(std::to_string(map[i][j].owner));
				playerJson["scr"] = Json::Value(std::to_string(1 * TOWER_SCORE));
				playerJson["cpN"] = Json::Value(std::to_string(0));
				playerJson["twN"] = Json::Value(std::to_string(1));
				playerJson["tw"].append(towerJson["id"]);
				data->currentRoundPlayerJson["player"].append(playerJson);
			}*/
		}
	}
#endif // SAVETXT

	//玩家信息TXT存档
#ifdef SAVETXT
	char bufferInfo[64];
	sprintf(bufferInfo, "#players\n");
	infoFile << bufferInfo;
	for (int i = 0; i < data->totalPlayers; i++)
	{
		char bufferPlayer[128];
		sprintf(bufferPlayer, "%d %s %d %d %d %d\n", i + 1, data->players[i].getName().c_str(), 0, 1, 1 * TOWER_SCORE, i + 1);
		infoFile << bufferPlayer;
	}
#endif // SAVETXT

	return true;
}

/***********************************************************************************************
*函数名 :【FC18】saveMapJson保存地图Json函数
*函数功能描述 : 将当前回合的地图Json数据保存到游戏所有回合的Json数据中，同时记录回合数
*函数参数 : 无
*函数返回值 : 无
*作者 : 姜永鹏
***********************************************************************************************/
void Map::saveMapJson() {
	//TRound round = data->getRound();      //更新地图Json前记录当前回合数
	//data->currentRoundMapJson["round"] = Json::Value(std::to_string(round));
	//data->mapInfoJsonRoot["map_logList"].append(data->currentRoundMapJson);
	data->lastRoundMapJson.clear();
	data->lastRoundMapJson = data->currentRoundMapJson;
	data->currentRoundMapJson.clear();
}


/***********************************************************************************************
*函数名 :【FC18】ShowInfo保存地图Json函数
*函数功能描述 : 将当前回合的地图Json数据保存到游戏所有回合的Json数据中，同时记录回合数
*函数参数 : x<int>--横坐标，y<int>--纵坐标
*函数返回值 : <mapBlockInfo>--地图方格信息
*作者 : 姜永鹏
***********************************************************************************************/
mapBlockInfo Map::ShowInfo(int x, int y) {
	mapBlockInfo info;
	info.type = map[y][x].type;
	info.owner = map[y][x].owner;
	info.occupyPoint = map[y][x].occupyPoint;
	info.towerIndex = map[y][x].TowerIndex;
	return info;
}


/***********************************************************************************************
*函数名 :【FC18】withinMap判断某点是否在地图范围内
*函数功能描述 : 判断点p是否在当前地图的范围内
*函数参数 : p<TPoint*>---指向所在点的指针
*函数返回值 : <mapBlockInfo>--地图方格信息
*作者 : 姜永鹏
***********************************************************************************************/
bool Map::withinMap(TPoint p) {
	return (p.m_x >= 0) && (p.m_x < m_width) && (p.m_y >= 0) && (p.m_y < m_height);
}

/***********************************************************************************************
*函数名 :【FC18】modifyOccupyPoint按塔所有者改变修改占有属性值
*函数功能描述 : 通过塔之前的拥有者（或共有，即无塔NOTOWER），以及现在的拥有者（同上），修改周围
                方格的占有属性值
*函数参数 : oldOwner<TPlayerID>--之前的拥有者ID，newOwner<TPlayerID>--现在的拥有者ID，p<TPoint>
            ---塔的所在点位坐标
*函数返回值 : 无
*作者 : 姜永鹏
***********************************************************************************************/
void Map::modifyOccupyPoint(TPlayerID oldOwner, TPlayerID newOwner, TPoint p) {
	if (!withinMap(p)) return;  //当前方格在地图之外
	if (oldOwner != NOTOWER && oldOwner >= 1 && oldOwner <= 4) map[p.m_y][p.m_x].occupyPoint[oldOwner - 1] -= INF;
	if (newOwner != NOTOWER && newOwner >= 1 && newOwner <= 4) map[p.m_y][p.m_x].occupyPoint[newOwner - 1] += INF;
	ownerChange(p);
	for (int i = p.m_y - 5; i <= p.m_y + 5; i++) {
		for (int j = p.m_x - 5; j <= p.m_x + 5; j++) {
			TPoint currentPoint = { j,i };
			TDist dist = getDist(currentPoint, p);
			if (!withinMap(currentPoint) || dist < 1 || dist > 5) continue;//点不在图上，离塔太近或太远
			if (data->getRound() == 0 && map[i][j].owner == PUBLIC) continue;  //开局不改变公共地盘的占有属性值
			if (oldOwner != NOTOWER) map[i][j].occupyPoint[oldOwner - 1] -= TowerOccupyPoint[dist - 1];
			if (newOwner != NOTOWER) map[i][j].occupyPoint[newOwner - 1] += TowerOccupyPoint[dist - 1];
			ownerChange(currentPoint);
		}
	}
}


/***********************************************************************************************
*函数名 :【FC18】ownerChang改变方格拥有者函数
*函数功能描述 : 改变位置p处方格拥有者，判定过渡区域
*函数参数 : p<TPoint>---所在方格的TPoint坐标
*函数返回值 : <TPlayerID>---塔当前所在方格变化后的所有者坐标（PUBLIC=0，公共区域，TRANSITION=-1
              过渡区域，OUTOFRANGE=-2在地图外）
*作者 : 姜永鹏
***********************************************************************************************/
TPlayerID Map::ownerChange(TPoint p) {
	if (!withinMap(p)) return OUTOFRANGE;    //当前方格在地图之外
	int maxOccupyPoint = -1, occupyID = PUBLIC;
	int maxOccupyCnt = 0;
	for (int i = 0; i < 4; i++) {
		if (map[p.m_y][p.m_x].occupyPoint[i] > maxOccupyPoint) {
			maxOccupyPoint = map[p.m_y][p.m_x].occupyPoint[i];
			occupyID = i + 1;
		}
	}
	if (maxOccupyPoint == 0) {
		map[p.m_y][p.m_x].owner = PUBLIC;
		return PUBLIC;
	}
	else {
		for (int i = 0; i < 4; i++) {
			if (map[p.m_y][p.m_x].occupyPoint[i] == maxOccupyPoint && ((i + 1) != occupyID)  && data->getRound() != 0)
			{
				map[p.m_y][p.m_x].owner = TRANSITION;
				return TRANSITION;
			}
		}
	}
	map[p.m_y][p.m_x].owner = occupyID;
	return occupyID;
}

/*****************************s******************************************************************
*函数名 :【FC18】showOwner判断方格拥有者函数
*函数功能描述 : 判断当前方格的拥有者
*函数参数 : p<TPoint>---所在方格的TPoint坐标
*函数返回值 :  <TPlayerID>---塔当前所在方格的所有者坐标（PUBLIC=0，公共区域，TRANSITION=-1过渡区
               域，OUTOFRANGE=-2在地图外）
*作者 : 姜永鹏
***********************************************************************************************/
TPlayerID Map::showOwner(TPoint p) {
	if (!withinMap(p)) return OUTOFRANGE;  //当前方格在地图之外
	else return map[p.m_y][p.m_x].owner;
}

/*****************************s******************************************************************
*函数名 :【FC18】clearAll清理掉兵团表格
*函数功能描述 : 判断当前方格的拥有者
*函数参数 : p<TPoint>---所在方格的TPoint坐标
*函数返回值 :  <TPlayerID>---塔当前所在方格的所有者坐标（PUBLIC=0，公共区域，TRANSITION=-1过渡区
			   域，OUTOFRANGE=-2在地图外）
*作者 : 姜永鹏
***********************************************************************************************/
void Map::clearAll(){
	delete[] data->players;
	data->players = nullptr;
}


/*****************************s******************************************************************
*函数名 :【FC18】saveMap保存本轮地图函数
*函数功能描述 : 将本轮游戏的地图以txt格式保存到文件中
*函数参数 : 无
*函数返回值 :  无
*作者 : 姜永鹏
***********************************************************************************************/
void Map::saveMap() {
	string map_save_path = log_path + ("/rand_map_save.txt");
	ofstream fileSaver(map_save_path, ios::app);
	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++) {
			char map_save_unit[256];
			mapBlock map_unit = map[i][j];
			sprintf(map_save_unit, "%d %d %d %d %d", j, i, map_unit.type, map_unit.owner, map_unit.TowerIndex);
			fileSaver << map_save_unit;
			for (int k = 0; k < 4; k++) {
				char temp_occupyP[32];
				sprintf(temp_occupyP, " %d", map_unit.occupyPoint[k]);
				fileSaver << temp_occupyP;
			}
			fileSaver << "\n";
		}
	}
	fileSaver.close();
}


/*****************************s******************************************************************
*函数名 :【FC18】saveMap保存本轮地图函数
*函数功能描述 : 将本轮游戏的地图以txt格式保存到文件中
*函数参数 : 无
*函数返回值 :  无
*作者 : 姜永鹏
***********************************************************************************************/
bool Map::recoverFromMap(vector<pair<TPoint, TPoint>>& towerPoint) {
	int blockCnt = 0;
	string map_path = read_path + ("/rand_map_save.txt");
	ifstream in(map_path);
	if (!in) return false;
	string save_map_line;
	while (getline(in, save_map_line)) {
		int i, j;
		mapBlock tempBlock;
		tempBlock.occupyPoint.resize(4);
		sscanf(save_map_line.c_str(), "%d %d %d %d %d %d %d %d %d"  , &i
			                                                        , &j
			                                                        , &tempBlock.type
			                                                        , &tempBlock.owner
			                                                        , &tempBlock.TowerIndex
			                                                        , &tempBlock.occupyPoint[0]
			                                                        , &tempBlock.occupyPoint[1]
		                                                            , &tempBlock.occupyPoint[2]
		                                                            , &tempBlock.occupyPoint[3]);
		if (tempBlock.TowerIndex != NOTOWER) {
			towerPoint[tempBlock.TowerIndex] = { {i, j}, {i ,j} };
		}
		map[j][i] = tempBlock;
		blockCnt++;
	}
	if (blockCnt != m_height * m_width) return false;
	return true;
}