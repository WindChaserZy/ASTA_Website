#include "player.h"
using std::vector;


Player::Player()
{
	alive = true;
	deadRound = -1;
	m_id = -1;
	data = nullptr;
	conqueTowerNum = 0;
	eliminateCorpsNum = 0;
	captureCorpsNum = 0;
	rank = -1;
	score = -1;
}

//#json
Player::Player(Player& _player)// copy����player
{
	m_crops = _player.getCrops();
	m_tower = _player.getTower();
	alive = _player.isAlive();
	m_id = _player.getId();
	conqueTowerNum = _player.getCqTowerNum();
	eliminateCorpsNum = _player.getElCorpsNum();
	captureCorpsNum = _player.getCqCorpsNum();
	name = _player.getName();
	rank = _player.getRank();
	score = _player.getScore();
	deadRound = _player.getdeadRound();

	data = _player.data;   //����ǳ����?

}


Player::~Player()
{
}


//ɱ�����
void Player::Kill()
{
	alive = false;
	deadRound = std::ceil(data->getRound() / 4.0); //���������غ����Ǵ�غ���
}

/***********************************************************************************************
*������ :��FC18��getPlayScore��ȡ��ҵ÷�
*������������ : ������ҵķ������ͱ�����Ϣ��������ҵ�ǰ�÷֣���������
*�������� : �ޣ�ֱ����Player�����
*��������ֵ : <int>��ֵ
*���� : ������
***********************************************************************************************/
int Player::getPlayerScore(DATA::Data * d) {

	if (isAlive() == false)   //����Ѿ����֣����ݳ��ֵĻغ�����¼���з�ֵ
		return deadRound - MAX_ROUND;
	TScore totalScore = 0;
	for (int map_i = 0; map_i < data->gameMap.getHeigth(); map_i++) {
		for (int map_j = 0; map_j < data->gameMap.getWidth(); map_j++) {
			if (data->gameMap.map[map_i][map_j].owner == m_id)
				totalScore++;
		}
	}
	//TScore corpsScore, towerScore, killScore;
	//corpsScore = towerScore = killScore = 0;
	/*for (TCorpsID i : m_crops)
	{
		if (data->myCorps[i].getType() == Battle)  //�����Ǽ���0��ʼ[!!!����ȷ��]
			corpsScore += BATTLE_CORP_SCORE * (data->myCorps[i].getLevel() + 1);
		else if (data->myCorps[i].getType() == Construct)
			corpsScore += CONSTRUCT_CORP_SCORE * 1;
	}*/
	//corpsScore += CORP_SCORE * m_crops.size();
	//for (TTowerID i : m_tower)
	//{
	//	towerScore += TOWER_SCORE * (data->myTowers[i].getLevel());             //�������ȼ���1��ʼ[!!!����ȷ��]
	//}
	//killScore += (conqueTowerNum + eliminateCorpsNum + captureCorpsNum) * KILL_SCORE;
	//TScore totalScore = corpsScore + towerScore + killScore;
	//setScore(totalScore);
	return totalScore;
}

/***********************************************************************************************
*������ :��FC18��addCrops
*������������ : ��m_crops�����ID���ڱ��Ź���ʱ����
*�������� : ��ӵı���ID
*��������ֵ : ��
*���� : ������
***********************************************************************************************/
void Player::addCrops(TCorpsID ID)
{
	m_crops.insert(ID);
}

/***********************************************************************************************
*������ :��FC18��deleteCrops
*������������ : ��m_crops��ɾ��ID���ڱ����ڲ���⵽HPΪ0ʱ����
*�������� : ɾ���ı���ID
*��������ֵ : ��
*���� : ������
***********************************************************************************************/
void Player::deleteCrops(TCorpsID ID)
{
	m_crops.erase(ID);
}
/***********************************************************************************************
*������ :��FC18��towerNumControl�ж���ҷ��������Ƿ���
*������������ : �ж���ҷ�������Ŀ�Ƿ񳬹���������������
*�������� : ��
*��������ֵ : <bool>---�Ƿ񳬹����ƣ�true---�ǣ�false---��
*���� : ������
***********************************************************************************************/
bool Player::towerNumControl() {
	if (getTower().size() >= MAX_TOWER_NUM) return true;
	else return false;
}
/***********************************************************************************************
*������ :��FC18��corpsNumControl�ж���ұ������Ƿ���
*������������ : �ж���ұ�����Ŀ�Ƿ񳬹�������������
*�������� : ��
*��������ֵ : <bool>---�Ƿ񳬹����ƣ�true---�ǣ�false---��
*���� : ������
***********************************************************************************************/
bool Player::battleNumControl() {
	int battleNum = 0;
	for (TCorpsID c : getCrops())
	{
		if (data->myCorps[c].getType() == Battle) battleNum++;
		if (battleNum >= MAX_BATTLE_NUM)
		{
			return true;
		}
	}
	return false;
}
/***********************************************************************************************
*������ :��FC18��corpsNumControl�ж���ұ������Ƿ���
*������������ : �ж���ұ�����Ŀ�Ƿ񳬹�������������
*�������� : ��
*��������ֵ : <bool>---�Ƿ񳬹����ƣ�true---�ǣ�false---��
*���� : ������
***********************************************************************************************/
bool Player::constructNumControl() {
	int constructNum = 0;
	for (TCorpsID c : getCrops())
	{
		if (data->myCorps[c].getType() == Construct) constructNum++;
		if (constructNum >= MAX_CONSTRUCT_NUM)
		{
			return true;
		}
	}
	return false;
}