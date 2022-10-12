/***
 * judge端执行ICamp和IPlayer的asJson方法，将得到的两个json对象传给选手，选手将两歌json导进自己ICamp和IPlayer的data里面。
 * 选手每次运行get**的方法时就从data里面拿东西返回，执行命令操作时把命令放在IPlayer的action里面，把action反馈给裁判程序去doAction即可
***/

#ifndef INTERFACE_H_
#define INTERFACE_H_
#include <vector>
#include "../json/json.h"
using std::vector;
class ICamp
{
public:
	virtual int** getCurrentPlants() = 0;
	virtual int*** getCurrentZombies() = 0;
	virtual int getSun() = 0;
	virtual int* getPlantCD() = 0;
	virtual int* getLeftLines() = 0;
	virtual int getRows() = 0;
	virtual int getColumns() = 0;
	virtual int getCurrentType() = 0;
	virtual ~ICamp() = default;
	Json::Value asJson(){
		Json::Value result;
		result["getSun"] = getSun();
		result["getRows"] = getRows();
		result["getColumns"] = getColumns();
		result["getCurrentType"] = getCurrentType();

		int** plants = getCurrentPlants();
		Json::Value plantArray;
		for (int i = 0; i < 5; i++){
			Json::Value plantLineArray;
			for (int j = 0; j < 10; j++){
				plantLineArray.append(plants[i][j]);
			}
			plantArray.append(plantLineArray);
		}
		result["getCurrentPlants"] = plantArray;

		
		int*** zombies = getCurrentZombies();
		Json::Value zombiesArray;
		for (int i = 0; i < 5; i++){
			Json::Value zombiesLineArray;
			for (int j = 0; j < 10; j++){
				Json::Value zombiesCellArray;
				for (int k = 0; zombies[i][j][k]!=-1; k++){
					zombiesCellArray.append(zombies[i][j][k]);
				}
				zombiesLineArray.append(zombiesCellArray);
			}
			zombiesArray.append(zombiesLineArray);
		}
		result["getCurrentZombies"] = zombiesArray;

		Json::Value plantCDArray;
		int* plantCD = getPlantCD();
		int length = (getCurrentType() == 0 ? 6 : 5);
		for (int i = 0; i < length; i++){
			plantCDArray.append(plantCD[i]);
		}
		result["getPlantCD"] = plantCDArray;


		Json::Value leftLinesArray;
		int* leftLines = getLeftLines();
		for (int i = 0; i < 5; i++){
			leftLinesArray.append(leftLines[i]);
		}
		result["getLeftLines"] = leftLinesArray;

		return result;
	}
};
class IPlayer
{
public:
	ICamp* Camp;
	virtual void PlacePlant(int type, int x, int y) = 0;
	virtual void PlaceZombie(int type, int y) = 0;
	virtual int getTime() = 0;
	virtual int getScore() = 0;
	virtual int getKillPlantsScore() = 0;
	virtual int getKillZombiesScore() = 0;
	virtual int getNotBrokenLines() = 0;
	virtual int getBrokenLinesScore() = 0;
	virtual int getLeftPlants() = 0;
	virtual void removePlant(int x, int y) = 0;
	virtual ~IPlayer()
	{
		delete Camp;
		Camp = nullptr;
	}
	Json::Value asJson(){
		Json::Value result;
		result["getTime"] = getTime();
		result["getScore"] = getScore();
		result["getKillPlantsScore"] = getKillPlantsScore();
		result["getKillZombiesScore"] = getKillZombiesScore();
		result["getNotBrokenLines"] = getNotBrokenLines();
		result["getBrokenLinesScore"] = getBrokenLinesScore();
		result["getLeftPlants"] = getLeftPlants();
		return result;
	}
	void doAction(Json::Value actionList){
		for (int i = 0; i < actionList.size(); i++){
			Json::Value action = actionList[i];
			if (action["name"] == string("PlacePlant")){
				PlacePlant(action["type"].asInt(), action["x"].asInt(), action["y"].asInt());
			}
			if (action["name"] == string("PlaceZombie")){
				PlaceZombie(action["type"].asInt(), action["y"].asInt());
			}
			if (action["name"] == string("removePlant")){
				removePlant(action["x"].asInt(), action["y"].asInt());
			}
		}
	}
};

#endif