#pragma once

#include "definition.h"
#include "Crops.h"
#include "tower.h"
#include <set>
#include "data.h"
class Player                                                                //@@@��FC18�������
{
public:
	Player();                                                               //@@@��FC18�������Ĭ�Ϲ��캯��
	Player(Player&);                                                        //@@@��FC18������ิ�ƹ��캯��   #json
	~Player();                                                              //��FC18���������������
	//���ӿƼ�����
	void setdata(DATA::Data* d) { data = d; }                               //��FC18�����ø�������Data
	DATA::Data* getdata() { return data; }
	bool isAlive() { return alive; }                                        //��FC18���ж�����Ƿ����
	//int maxControlNumber();                                                 //@@@��FC18������������ô�ģ���֪���ò��ã���ȡ�����������
	void Kill();                                                            //��FC18�������������
	int getdeadRound() { return deadRound; }                                //��FC18����ȡ�����غ�
	void setdeadRound(int d) { deadRound = d; }                             //��FC18�����������غ�
	//@@@��FC18����ȡ��ҵ�ǰ�÷֣����չ����������鿼�ǵ�ͬ����ʱ��ʲôָ�����Ƚϵȣ�
	int getPlayerScore(DATA::Data* d);
	void setID(TPlayerID id) { m_id = id; }
	TPlayerID getId() { return m_id; }                                      //��FC18����ȡ���ID
	int getCqTowerNum() { return conqueTowerNum; }                          //��FC18����ȡ���ռ��з���������
	int getElCorpsNum() { return eliminateCorpsNum; }                       //��FC18����ȡ�������з�������
	int getCqCorpsNum() { return captureCorpsNum; }                         //��FC18����ȡ��ҷ�²�ط�������
	void setCqTowerNum(int num) { conqueTowerNum = num; }                   //��FC18���������ռ��з���������
	void setElCorpsNum(int num) { eliminateCorpsNum = num; }                //��FC18�������������з�������
	void setCqCorpsNum(int num) { captureCorpsNum = num; }                  //��FC18��������ҷ�²�ط�������
	bool towerNumControl();                                      //��FC18����ҷ�������Ŀ���
	bool battleNumControl();                                      //��FC18�������ս������Ŀ���
	bool constructNumControl();                                      //��FC18����ҹ��̱�����Ŀ���
	//��FC18����ȡ��ҵ����з�����set
	std::set<TTowerID>& getTower() { return m_tower; }

	//��FC18����ȡ��ҵ����б��ŵ�set
	std::set<TCorpsID>& getCrops() { return m_crops; }

	//��FC18����ӱ���
	void addCrops(TCorpsID ID);
	//��FC18��ɾ������
	void deleteCrops(TCorpsID ID);
	//��FC18����ȡ�������
	int getRank() { return rank; }
	//��FC18�������������
	void setRank(int Rank) { rank = Rank; }
	//��FC18����ȡ�������
	string getName() { return name; }
	//��FC18�������������
	void setName(string Name) { name = Name; }
	//��FC18����ȡ��һ���
	TScore getScore() { return score; }
	//��FC18��������һ���
	void setScore(TScore Score) { score = Score; }
	//��FC18�������һ���
	TScore getScore(TScore Score) { return score; }


private:
	bool alive = true;                                                      //��FC18���ǲ��ǻ�����
	int deadRound;                                                          //��FC18�������Ļغ�
	DATA::Data* data;                                                       //��FC18�����ݵĴ洢�빲��
	TPlayerID m_id;                                                         //��FC18�����ID
	string name;                                                            //��FC18����ҵ�����
	int conqueTowerNum;                                                     //��FC18�����ռ���������
	int eliminateCorpsNum;                                                  //��FC18���������о���������
	int captureCorpsNum;                                                    //��FC18������²�ı�����
	//@@@��FC18����ҷ�²�о���������
	//@@@��FC18��ָ��ǰ������з�������set���ݽṹ���ο�ԭ����std::set<TCellID> m_cells
	std::set<TTowerID> m_tower;
	
	//@@@��FC18��������б��ŵ���ţ�����Ҳ��set�������ݽṹ���ڲ��������������������
	std::set<TCorpsID> m_crops;//�ɱ������ڲ��޸�
	
	int rank;   //��FC18���������
	int score;  //��FC18����һ���
};

