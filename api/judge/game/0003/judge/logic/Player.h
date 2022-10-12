#ifndef PLAYER_H_
#define PLAYER_H_
#include "Game.h"
#include "Interface.h"

#ifdef _DEBUG

#define new  new(_NORMAL_BLOCK, __FILE__, __LINE__)

#endif
class Player :public IPlayer                                                             //@@@��FC19�������
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
	}                                    //@@@��FC19�������Ĭ�Ϲ��캯��
	~Player()
	{
	}//��FC19���������������
	//@@@��FC19����ȡ��ҵ�ǰ�÷֣����չ����������鿼�ǵ�ͬ����ʱ��ʲôָ�����Ƚϵȣ�
	int getBrokenLinesScore() { return BrokenLines; }                          //��FC19����ȡ��ʬ����ռ����
	int getNotBrokenLines() { return NotBrokenLinesNum; }                 //��FC19����ȡֲ�﷽��������
	//�ɵ���Ϊ���������ָ������												
	int getKillPlantsScore() { return KillPlants; } 							 //��FC19����ȡ��ɱֲ����Ŀ		
	int getKillZombiesScore() { return KillZombies; }                          //��FC19����ȡ��ɱ��ʬ��Ŀ   
	int getLeftPlants() { return LeftPlants; }                                //��FC19����ȡʣ��ֲ����Ŀ
	void setBrokenLines(int num) { BrokenLines = num; }                     //��FC19�����±���
	void setNotBrokenLinesNum(int num) { NotBrokenLinesNum = num; }
	void setLeftPlants(int num) { LeftPlants = num; }
	void setKillPlants(int num) { KillPlants = num; }
	void setKillZombies(int num) { KillZombies = num; }
	//��FC19����ȡ��һ���
	int getScore() { return score; }
	//��FC19��������һ���
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
	//��FC19�����ID
	int BrokenLines;
	int NotBrokenLinesNum;
	int KillPlants;
	int KillZombies;
	int LeftPlants;
	int score;  //��FC19����һ���
};





#endif