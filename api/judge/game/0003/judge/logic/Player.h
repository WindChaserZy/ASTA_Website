#ifndef PLAYER_H_
#define PLAYER_H_
#include "Game.h"
#include "Interface.h"

#ifdef _DEBUG

#define new  new(_NORMAL_BLOCK, __FILE__, __LINE__)

#endif
class Player :public IPlayer                                                             //@@@【FC19】玩家类
{
public:
	Player(ICamp* _ICamp)
	{
		Camp = _ICamp;
		BrokenLines = 0;
		NotBrokenLinesNum = 0;
		LeftPlants = 0;
		KillPlants = 0;
		KillZombies = 0;
		score = 0;
	}                                    //@@@【FC19】玩家类默认构造函数
	~Player()
	{
	}//【FC19】玩家类析构函数
	//@@@【FC19】获取玩家当前得分（按照规则来，建议考虑到同名次时按什么指标来比较等）
	int getBrokenLinesScore() { return BrokenLines; }                          //【FC19】获取僵尸方攻占行数
	int getNotBrokenLines() { return NotBrokenLinesNum; }                 //【FC19】获取植物方保留行数
	//可调整为数组或其余指针类型												
	int getKillPlantsScore() { return KillPlants; } 							 //【FC19】获取击杀植物数目		
	int getKillZombiesScore() { return KillZombies; }                          //【FC19】获取击杀僵尸数目   
	int getLeftPlants() { return LeftPlants; }                                //【FC19】获取剩余植物数目
	void setBrokenLines(int num) { BrokenLines = num; }                     //【FC19】更新变量
	void setNotBrokenLinesNum(int num) { NotBrokenLinesNum = num; }
	void setLeftPlants(int num) { LeftPlants = num; }
	void setKillPlants(int num) { KillPlants = num; }
	void setKillZombies(int num) { KillZombies = num; }
	//【FC19】获取玩家积分
	int getScore() { return score; }
	//【FC19】设置玩家积分
	void setScore(int Score) { score = Score; }
	
	void setCamp(ICamp* camp) {
		Camp = camp;
	}
	int getTime() {
		return Game::getTime();
	}
	void PlacePlant(int type, int x, int y)
	{
		if(Camp->getCurrentType() == 0)
		{
			commands.addCommand(type, x, y);
		}
	}
	void PlaceZombie(int type, int y)
	{
		if(Camp->getCurrentType() == 1)
		{
			commands.addCommand(type, y);
		}
	}
	void removePlant(int x, int y)
	{
		if(Camp->getCurrentType() == 0)
		{
			commands.addCommand(-1, x, y);
		}
	}
	CommandList commands;
private:
	//【FC19】玩家ID
	int BrokenLines;
	int NotBrokenLinesNum;
	int KillPlants;
	int KillZombies;
	int LeftPlants;
	int score;  //【FC19】玩家积分
};





#endif