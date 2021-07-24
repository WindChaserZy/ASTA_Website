#include "tower.h"

TTowerID Tower::ID = 0;

Tower::Tower(void) :m_data(nullptr)
{
}
Tower::~Tower(void)
{
}




//���캯���������Գ�ʼ��
Tower::Tower(DATA::Data* _data, TPlayerID m_playid, TPoint pos) :m_data(_data)
{
	m_PlayerID = m_playid;
	m_position = pos;
	m_id = ID;
	ID++;//�����ٸ���tower���ID
	m_exsit = true;
	m_level = 1;//��ʼ�ȼ�Ϊ1  
	set_all(m_level);
	m_healthpoint = M_healthpoint;
	m_experpoint = 0;//��ʼ����ֵΪ0
	m_producttype = NOTASK;
	m_productconsume = 0;
	for (int i = 0; i < 6; i++)
		task_cache[i] = 0;
	//����data
	m_data->totalTowers++;
	m_data->players[m_PlayerID - 1].getTower().insert(m_id);
	m_data->gameMap.map[m_position.m_y][m_position.m_x].TowerIndex = m_id;
	//by jyp:��������֮���޸ķ������Ϊ��
	//m_data->gameMap.map[m_position.m_y][m_position.m_x].type = TRTower;
	//by jyp : ��¼�½�����ID
	m_data->newTower.insert(m_id);
	//����occupypoint/owner
	m_data->gameMap.modifyOccupyPoint(NOTOWER, m_PlayerID, m_position);
}



/*
���ƣ�set_all
���ܣ����ݵȼ�����������������ֵ��ս�������������辭��ֵ��������Χ
��������ǰ�ȼ�
by lxj
*/
void Tower::set_all(int level)
{
	m_productpoint = TowerInitConfig[level - 1].initBuildPoint;
	M_healthpoint = TowerInitConfig[level - 1].initHealthPoint;
	m_battlepoint = TowerInitConfig[level - 1].initProductPoint;
	m_upgradexper = TowerInitConfig[level - 1].upgradeExper;
	m_attackrange = TowerInitConfig[level - 1].battleRegion;
}




/*
���ƣ�upgrade
���ܣ������������������ʱִ�еĲ���
by lxj
*/
void Tower::upgrade()
{
	m_level++;
	if (m_level > MAX_TOWER_LEVEL) //���ó������ȼ�
		m_level = MAX_TOWER_LEVEL;
	THealthPoint old_Mhp = M_healthpoint;
	set_all(m_level);
	//ʵ������ֵ������ֵ���޳ɱ����ı�
	m_healthpoint = (M_healthpoint * m_healthpoint) / old_Mhp;
}




/*
���ƣ�level_upgrade
���ܣ����ݵ�ǰ����ֵ���µȼ�
����ֵ���Ƿ�����
by lxj
*/
bool Tower::set_level() 
{
	bool upgrade;
	upgrade = false;
	//�غϿ�ʼ�ۼ���һ�غ����þ���ֵ
	int bonus = 0;
	int m_round = floor(m_data->getRound() - 1 / 4.0F);
	if (m_round >= 0 && m_round < 100)
		bonus = 5;
	if (m_round >= 100 && m_round < 200)
		bonus = 10;
	if (m_round >= 200 && m_round <= 300)
		bonus = 15;
	m_experpoint += bonus;
	//����
	if (m_level >= MAX_TOWER_LEVEL)
		return false;
	//δ����
	if (m_experpoint >= m_upgradexper)//����ֵ������������
	{
		m_level += 1;
		m_experpoint -= m_upgradexper;//���µ�ǰ����ֵ
		set_all(m_level);//�������µ�ǰ�ȼ��������辭��
		upgrade = true;		
	}
	return upgrade;
}



/*
���ƣ�product_crops
���ܣ���������
��������������������
by lxj
*/
void Tower::product_crops(productType protype)
{
	if (m_data->players[m_PlayerID - 1].battleNumControl() == false) {
		if (protype == PWarrior)
		{
			Crops temp(m_data, Battle, Warrior, Builder, m_PlayerID, m_position);
			m_data->myCorps.push_back(temp);
			m_data->changeCorps.insert(temp.getID());
		}
		else if (protype == PArcher)
		{
			Crops temp(m_data, Battle, Archer, Builder, m_PlayerID, m_position);
			m_data->myCorps.push_back(temp);
			m_data->changeCorps.insert(temp.getID());
		}
		else if (protype == PCavalry)
		{
			Crops temp(m_data, Battle, Cavalry, Builder, m_PlayerID, m_position);
			m_data->myCorps.push_back(temp);
			m_data->changeCorps.insert(temp.getID());
		}
	}
	if (m_data->players[m_PlayerID - 1].constructNumControl() == false) {
		if (protype == PBuilder)
		{
			Crops temp(m_data, Construct, Warrior, Builder, m_PlayerID, m_position);
			m_data->myCorps.push_back(temp);
			m_data->changeCorps.insert(temp.getID());
		}
		else if (protype == PExtender)
		{
			Crops temp(m_data, Construct, Warrior, Extender, m_PlayerID, m_position);
			m_data->myCorps.push_back(temp);
			m_data->changeCorps.insert(temp.getID());
			//by jyp�������������������ڷ������ȼ���С1
			if (m_level > 1)
			{
				m_level--;
				THealthPoint old_Mhp = M_healthpoint;
				set_all(m_level);
				//ʵ������ֵ������ֵ���޳ɱ����ı�
				m_healthpoint = (M_healthpoint * m_healthpoint) / old_Mhp;
			}
		}
	}
}



/*
���ƣ�set_producttype
���ܣ������µ���������
�������������������� 
����ֵ���Ƿ����óɹ�
by lxj
*/
bool Tower::set_producttype(productType m_protype)
{
	//������������Խ�磺������ͣһ�غ�
	if (int(m_protype) < 0 || int(m_protype) > 5)
		return false;
	//����һ�غ�������������ɹ���������һ�غ�����Ľ���
	if (m_producttype != NOTASK)
		task_cache[int(m_producttype)] = m_productconsume;
	m_producttype = m_protype;
	//��������������Ϊ���״̬
	if (task_cache[(int)m_producttype] <= 0) 
	{
		if (m_producttype < 5)
		{
			m_productconsume = TowerProductCost[m_producttype];
			m_productconsume -= m_productpoint;
		}
		if (m_producttype == PUpgrade)
		{
			m_productconsume = 40 * m_level;
			m_productconsume -= m_productpoint;
		}
	}
	else
	{
		m_productconsume = task_cache[int(m_producttype)];
		m_productconsume -= m_productpoint;
	}
	m_data->changeTowers.insert(m_id);//by jyp:��¼������������ı�
	return true;
}



/*
���ƣ�get_towerbp
���ܣ��⵽���Ž���ʱ�����㿼�����������ս����
����ֵ������ս����(��������)
by lxj
*/
TBattlePoint Tower::get_towerbp()
{
	int bonus = 0;
	vector<TCorpsID> Unit = m_data->gameMap.map[m_position.m_y][m_position.m_x].corps;
	TCorpsID index;
	int baseBattlePoint = std::ceil((float)m_battlepoint * (float)m_healthpoint / (float)TowerInitConfig[m_level - 1].initHealthPoint);
	for (int i = 0; i < Unit.size(); i++)
	{
		index = Unit[i];
		if (m_data->myCorps[index].getPlayerID() != m_PlayerID)//�Ǽ�������
			continue;
		bonus += corpsBattleGain[m_data->myCorps[index].getbattleType()][0] * (m_data->myCorps[index].getLevel() + 1);
	}
	return (baseBattlePoint + bonus);
}




/*
���ƣ�Be_Attacked
���ܣ����Ź�����ʱ������������ֵ
����������ֵ��ʧ
����ֵ����������ֵ�Ƿ�Ϊ0����ռ/�ݻ٣�m_exsit = false��
by lxj
*/
bool Tower::Be_Attacked(TPlayerID enemy_id,THealthPoint hp_decrease, bool attackerAlive)
{
	m_healthpoint -= hp_decrease;
	m_data->changeTowers.insert(m_id);//by jyp:��¼��������ֵ�ȸı�
	if (m_healthpoint <= 0)
	{
		m_level -= 4;//���ĵȼ��½�4��
		TPlayerID oldOwner = m_PlayerID;//���������Ϣ
		//�����ݻ٣��ȼ�С��1/�����߷�������Ŀ��������
		if (m_level < 1 || m_data->players[enemy_id - 1].towerNumControl() == true)  
		{
			m_exsit = false;
			//����data
			m_data->totalTowers--;
			m_data->players[m_PlayerID - 1].getTower().erase(m_id);
			m_data->gameMap.map[m_position.m_y][m_position.m_x].TowerIndex = NOTOWER;
			//m_data->gameMap.map[m_position.m_y][m_position.m_x].type = TRPlain;//by jyp: �����ݻ�֮��ͳһ�޸ķ������Ϊƽԭ
			//by jyp : ��¼���ݻٵ�����ID
			m_data->dieTower.insert(m_id);
			//����occupypoint/owner
			m_data->gameMap.modifyOccupyPoint(m_PlayerID, NOTOWER, m_position);
			//�����ݻٸ��¹�����ռ������
			int currentCqTowerNum = m_data->players[enemy_id - 1].getCqTowerNum();
			m_data->players[enemy_id - 1].setCqTowerNum(currentCqTowerNum + 1);
		}
		//������������ţ����������Ļ��ж�����������������ռ�죩��������ռ
		else if (attackerAlive == true)
		{
			set_all(m_level);
			//����ֵ����
			m_healthpoint = M_healthpoint;
			m_data->players[m_PlayerID - 1].getTower().erase(m_id);//�޸�ԭӵ���ߵ����б�
			m_data->players[enemy_id - 1].getTower().insert(m_id);//�޸���ӵ���ߵ����б�
			//����occupypoint/owner
			m_data->gameMap.modifyOccupyPoint(m_PlayerID, enemy_id, m_position);
			m_PlayerID = enemy_id;
			//������ռ���¹�����ռ������
			int currentCqTowerNum = m_data->players[enemy_id - 1].getCqTowerNum();
			m_data->players[enemy_id - 1].setCqTowerNum(currentCqTowerNum + 1);
		}
		else//����ռ��ʧ�ܣ����������߲��䣬����ǰ�ȼ����ø������ԣ�������
		{
			set_all(m_level);
			//����ֵ����
			m_healthpoint = M_healthpoint;
		}
		//�����ݻٻ�ռ�����ڷ��񼺷���������
		int newDieCorps = m_data->players[enemy_id - 1].getElCorpsNum();//��¼��������������
		TPoint towerPos = m_position;
		for (TCorpsID c : m_data->gameMap.map[towerPos.m_y][towerPos.m_x].corps)
		{
			if (m_data->myCorps[c].getPlayerID() == oldOwner)
			{
				m_data->myCorps[c].KillCorps();
				newDieCorps++;
			}
		}
		m_data->players[enemy_id - 1].setElCorpsNum(newDieCorps);
		return true;
	}
	return false;
}




/*
���ƣ�set_attacktarget
���ܣ����ù���Ŀ��
������Ŀ�����id
����ֵ���Ƿ񹥻��ɹ�
by lxj
*/
bool Tower::set_attacktarget(int crop_id) 
{
	//����ʧ��
	if (crop_id < 0 || crop_id >= m_data->myCorps.size())//idԽ��
		return false;
	if (m_data->myCorps[crop_id].isStation() == true)//����פ������
		return false;   
	if (m_data->myCorps[crop_id].getPlayerID() == m_PlayerID)//����Ŀ��Ϊ��������
		return false;
	Crops* enemy = &(m_data->myCorps[crop_id]);
	if (enemy->bAlive() == false)//��������
		return false;
	if (getDist(enemy->getPos(), m_position) > 2)//����������Χ
		return false;
	//����ǹ��̱����ж��Ƿ���ڻ���
	if (enemy->getType() == Construct)
	{
		Crops* colleage;
		TPoint pos = enemy->getPos();
		//�Ƿ���ڻ���
		for (int i = 0; i < m_data->gameMap.map[pos.m_y][pos.m_x].corps.size(); i++)
		{
			int index = m_data->gameMap.map[pos.m_y][pos.m_x].corps[i];
			colleage = &(m_data->myCorps[index]);
			if (colleage->getType() == Battle && colleage->getPlayerID() == enemy->getPlayerID())
				enemy = colleage;
		}
	}

	//�����ɹ�
	float deta = 0.04 * ((float)get_towerbp() - (float)enemy->getCE());
	int crop_lost = floor(30 * pow(2.71828, deta));
	enemy->BeAttacked(crop_lost, m_PlayerID, m_exsit);
	return true;
}


/*
���ƣ�Recover
���ܣ��������ظ�����ֵ
by lmx
*/
void Tower::Recover()
{
	struct TowerConfig levelInfo = TowerInitConfig[m_level-1];
	if (m_healthpoint != levelInfo.initHealthPoint) m_data->changeTowers.insert(m_id);   //by jyp:��¼��������ֵ�ı�
	m_healthpoint += floor(float(levelInfo.initHealthPoint)/3.0F);
	if(m_healthpoint >= levelInfo.initHealthPoint)
	{
		m_healthpoint = levelInfo.initHealthPoint;
	}
}

