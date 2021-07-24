#pragma once

#ifndef TOWER_H
#define TOWER_H

#include "definition.h"
#include "data.h"
#include "Crops.h"
#include "player.h"

class Tower
{
private:
	//��Ϸ��Ϣ
	DATA::Data* 		m_data;

	//����Ϣ
	static TTowerID		ID;
	TTowerID			m_id;//��ID
	TPlayerID			m_PlayerID;//�������ID
	bool				m_exsit;//���Ƿ�����ȼ��Ƿ����1
	TPoint				m_position;//λ��

	//������
	TProductPoint       m_productpoint;//������
	productType			m_producttype;//������������
	THealthPoint        m_healthpoint;//����ֵ
	THealthPoint		M_healthpoint;//����ֵ����
	TBattlePoint        m_battlepoint;//ս����
	TExperPoint			m_experpoint;//����ֵ
	int					m_level;//�ȼ�:��1��ʼ               
	int					m_attackrange;//������Χ     

	//��������
	TExperPoint			m_upgradexper;//��������һ�����辭��ֵ
	int					m_productconsume;//��ǰ���������Ӧ������������ֵ	
	int					task_cache[6];//����δ���������ȣ��������������������ֵ����Ϊ0����Ϊ���״̬��
public:
	Tower(void);
	~Tower(void);
	//�����캯��
	Tower(DATA::Data* _data, TPlayerID m_playid, TPoint pos);
	//�����ƹ��캯��
	//Tower(const Tower& tower);

	/*������*/
	//���ݵȼ�������������
	void set_all(int level);
	//ÿ�غϳ�ʼ���ݾ���ֵ�ж��Ƿ�����
	bool set_level();
	//���á�������״̬
	void set_notask() { task_cache[m_producttype] = 0; m_producttype = NOTASK; }
	//�ж���һ�غ����������Ƿ����
	bool protask_finish()
	{
		if (m_productconsume <= 0)
			return true;
		return false;
	}
	//��������������
	bool set_producttype(productType m_protype);
	//�����������Ļ������
	void clear_cache(productType task_clear) { task_cache[task_clear] = 0; }
	//��������
	void product_crops(productType protype);
	//������
	void upgrade();
	//���ù���Ŀ��
	bool set_attacktarget(int crop_id);
	



	/*��Ϣ��ȡ*/
	//��ȡ�������ID
	const TPlayerID getPlayerID() { return m_PlayerID; }
	//��ȡ��λ��
	const TPoint getPosition() { return m_position; }
	//��ȡ���ȼ�
	int getLevel() { return m_level; }
	//��ȡ����ǰ�Ƿ���ȼ�С��1�����ݻ٣�
	bool getexsit() { return m_exsit; }
	//��ȡ��������
	TProductPoint getProductPoint() { return m_productpoint; }
	//��ȡ����������
	productType	getprotype() { return m_producttype; }
	//��ȡ������ֵ
	THealthPoint getHealthPoint() { return m_healthpoint; }
	//��ȡ��ս����
	TBattlePoint getBattlePoint() { return m_battlepoint; }
	//��ȡ������ֵ
	TExperPoint getExperPoint() { return m_experpoint; }
	//��ȡ��������Χ
	int getAttackRange() { return m_attackrange; }
	//��ȡ��ID
	TTowerID getTowerID() { return m_id; }

	/*�ṩ��������Ϣ*/
	TowerInfo ShowInfo() {
		TowerInfo info;
		info.exist = m_exsit;
		info.ID = m_id;
		info.ownerID = m_PlayerID;
		info.position = m_position;
		info.productPoint = m_productpoint;
		info.healthPoint = m_healthpoint;
		info.battlePoint = m_battlepoint;
		info.level = m_level;
		if(m_producttype == NOTASK)//û����������:NOTASK=-1
		{
			info.pdtType = NOTASK;
			info.productConsume = -1;
		}
		else
		{
			info.pdtType = m_producttype;
			info.productConsume = m_productconsume;
		}
		return info;
	}


	/*����ӿ�*/
	//�⵽���Ž���ʱ�����㿼�����������ս����
	TBattlePoint get_towerbp();
	//�������ŵĽ������������Ƿ񱻹���
	bool Be_Attacked(TPlayerID enemy_id, THealthPoint hp_decrease, bool attackerAlive);
	//�������ظ�����ֵ
	void Recover();
};
#endif