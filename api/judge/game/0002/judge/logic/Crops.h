#pragma once

#ifndef CROPS_H
#define CROPS_H

#include "definition.h"
#include "data.h"
#include "player.h"



class Crops
{
private:

	static TCorpsID		m_staticID;
	TCorpsID			m_myID;			//����ID
	corpsType			m_type;			//��������
	battleCorpsType		m_BattleType;	//ս������
	constructCorpsType	m_BuildType;	//�������
	TPlayerID			m_PlayerID;		//������Ӫ

	TMovePoint			m_MovePoint;	//�ж���
	THealthPoint		m_HealthPoint;	//����ֵ ��0������
	int					m_level;		//�ȼ� ��0��ʼ
	TBuildPoint			m_BuildPoint;	//�Ͷ���
	TPoint				m_position;		//λ��

//	int					m_PeaceNum;		//פ������ٸ��غ�û���ܵ�����
//	bool				m_bResting;		//�Ƿ�������

	DATA::Data* const	m_data;	//��Ϸ��Ϣ

	bool		m_bAlive;		//�Ƿ���

public:

	Crops(void);
	~Crops(void);
	Crops(DATA::Data* _data, corpsType type, battleCorpsType battletype, constructCorpsType buildtype, TPlayerID ID, TPoint pos);

	//���Ų���
	bool BeAttacked(int attack, TPlayerID ID, bool bAlive);	//��ս�����ܵ����� �����Ƿ��� �������
	bool Move(int dir);							//��ս�����ƶ� �����Ƿ�ɹ��ƶ�
	bool Attack(int type, TCorpsID ID, Command& c);			//���Ź���
	bool BuildTower();							//�����߽���
	void ChangeOwner(TPlayerID newowner);		//���Ÿı�����
	void KillCorps();							//��������
	void newRound();							//�»غϿ�ʼ
	void doChangingTerrain(terrainType target, int x, int y);   //���غϽ����޸ĵ���
	bool JudgeChangeTerrain(Command& c);                        //���غϽӵ��ĵ�������ж��ܷ��޸�

	bool MendTower();						//�жϽ�����Ƿ�����ڴ�����
	//bool ChangeTerrain(terrainType target);//�жϽ�����Ƿ�����ڴ˸��ĵ���

	//��ȡ��������

	bool bAlive();					//�Ƿ���
	TBattlePoint getCE();			//��ȡս����
	struct CorpsInfo ShowInfo();	//�ṩ������Ϣ
	TCorpsID getID() { return m_myID; }		//��ȡ��ǰ���ŵ�id
	corpsType getType() { return m_type; }	//��ȡ��ǰ���ŵ�����
	int getLevel() { return m_level; }		//��ȡ��ǰ���ŵ��Ǽ�����0��ʼ��
	TPoint getPos() { return m_position; }	//��ȡ��ǰ���ŵ�λ��
	battleCorpsType getbattleType() { return m_BattleType; }	//��ȡ��ǰս�����ŵ�����
	TPlayerID getPlayerID() { return m_PlayerID; }				//��ȡ����������Ӫ
	bool isStation();


	//void haveCmd();								//�������� �˳��Զ�����״̬
	//bool GoRest();								//���Ž���פ������״̬
	
protected:

	void ResetMP();	//�����ж���
	void AttackCrops(Crops* enemy);			//��ս���Ź���
	void AttackTower(class Tower *enemy);	//��ս���Ź�����
	void UpdatePos(TPoint targetpos);		//����λ��ʱ��Ҫ���е�ͳһ����
	bool IsNeighbor(TPoint point);			//�ж��Ƿ�����
	bool IsInRange(TPoint point);			//�ж��Ƿ��ڹ�����Χ��
	//void Recover();	//�ظ�HP
};

#endif