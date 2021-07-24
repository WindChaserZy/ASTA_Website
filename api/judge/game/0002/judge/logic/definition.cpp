#include "definition.h"
#include <cmath>
#include <algorithm>
TPoint operator-(const TPoint& p1, const TPoint& p2)
{
	TPoint ret;
	ret.m_x = p1.m_x - p2.m_x;
	ret.m_y = p1.m_y - p2.m_y;
	return ret;
}

TLength getDistance(const TPoint& p1, const TPoint& p2)
{
	TPoint distance = p1 - p2;
	return sqrt(distance.m_x*distance.m_x + distance.m_y*distance.m_y);
}

int generateRanInt(int start, int end) {
	return rand() % (end - start + 1) + start;
}

std::ostream& operator<<(std::ostream& os, const CommandList& cl)
{
	//FC15�ɴ���
	return os;
}


/***********************************************************************************************
*������ :��FC18��getDist��ȡ���뺯������
*������������ : ����FC18��������������֮��ľ���
*�������� : p1<const TPoint&>--��1���㣬p2<const TPOint&>--��2����
*��������ֵ : <TPoint>����
*���� : ������
***********************************************************************************************/
TDist getDist(const TPoint& p1, const TPoint& p2) {
	TPoint dp = p1 - p2;
	int dx = dp.m_x;
	int dy = dp.m_y;
	return max(abs(dx), abs(dy));
}


/***********************************************************************************************
*������ :��FC18��getDist��ȡ���뺯������
*������������ : ͨ���ļ����뵱ǰ��Ϸ�ĵ�ͼ���ݡ�����������ݣ�����ʼ��������飬д����غ�����
				Json
*�������� : inMap<ifstream&> �����ļ�������enableOutput<bool> �Ƿ����������Ϣ��true--����
			false--������
*��������ֵ : false--�����ͼʧ�ܣ�true--�����ͼ�ɹ�
*���� : ������
***********************************************************************************************/
TDist getDist(const int p1_x, const int p1_y, const int p2_x, const int p2_y) {
	int dx = p1_x - p2_x;
	int dy = p1_y - p2_y;
	return max(abs(dx), abs(dy));
}

TowerInfo::TowerInfo(Json::Value json){
	position.m_x = json["position"][0].asInt();
	position.m_y = json["position"][1].asInt();

	exist = json["exist"].asBool();
	ID = json["ID"].asInt();
	ownerID = json["ownerID"].asInt();
	productPoint = json["productPoint"].asInt();
	pdtType = productType(json["pdtType"].asInt());
	productConsume = json["productConsume"].asInt();
	battlePoint = json["battlePoint"].asInt();
	healthPoint = json["healthPoint"].asInt();
	level = json["level"].asInt();
}
Json::Value TowerInfo::asJson() const{
	Json::Value result;

	Json::Value posJson;
	posJson.append(position.m_x);
	posJson.append(position.m_y);
	result["position"] = posJson;

	result["exist"] = exist;
	result["ID"] = ID;
	result["ownerID"] = ownerID;
	result["productPoint"] = productPoint;
	result["pdtType"] = pdtType;
	result["productConsume"] = productConsume;
	result["battlePoint"] = battlePoint;
	result["healthPoint"] = healthPoint;
	result["level"] = level;
	return result;
}


CorpsInfo::CorpsInfo(Json::Value json){
	pos.m_x = json["pos"][0].asInt();
	pos.m_y = json["pos"][1].asInt();

	exist = json["exist"].asBool();
	ID = json["ID"].asInt();
	HealthPoint = json["HealthPoint"].asInt();
	BuildPoint = json["BuildPoint"].asInt();
	owner = json["owner"].asInt();
	type = corpsType(json["type"].asInt());
	movePoint = json["movePoint"].asInt();
	m_BattleType = battleCorpsType(json["m_BattleType"].asInt());
	m_BuildType = constructCorpsType(json["m_BuildType"].asInt());
}
Json::Value CorpsInfo::asJson() const{
	Json::Value result;

	Json::Value posJson;
	posJson.append(pos.m_x);
	posJson.append(pos.m_y);
	result["pos"] = posJson;
	
	result["exist"] = exist;
	result["ID"] = ID;
	result["HealthPoint"] = HealthPoint;
	result["BuildPoint"] = BuildPoint;
	result["owner"] = owner;
	result["type"] = type;
	result["movePoint"] = movePoint;
	result["m_BattleType"] = m_BattleType;
	result["m_BuildType"] = m_BuildType;
	return result;
}


PlayerInfo::PlayerInfo(Json::Value json){
	id = json["id"].asInt();
	rank = json["rank"].asInt();
	alive = json["alive"].asBool();
	tower.clear();
	for (int i = 0; i < json["tower"].size(); i++){
		tower.insert(json["tower"][i].asInt());
	}
	corps.clear();
	for (int i = 0; i < json["corps"].size(); i++){
		corps.insert(json["corps"][i].asInt());
	}
}
Json::Value PlayerInfo::asJson() const{
	Json::Value result;
	result["id"] = id;
	result["rank"] = rank;
	result["alive"] = alive;

	Json::Value towerArray;
	for (TTowerID i: tower){
		towerArray.append(i);
	}
	result["tower"] = towerArray;

	Json::Value corpsArray;
	for (TCorpsID i: corps){
		corpsArray.append(i);
	}
	result["corps"] = corpsArray;

	return result;
}


mapBlock::mapBlock(Json::Value json){
	type = terrainType(json["type"].asInt());
	owner = terrainType(json["owner"].asInt());
	TowerIndex = terrainType(json["TowerIndex"].asInt());
	occupyPoint.clear();
	for (int i = 0; i < json["occupyPoint"].size(); i++){
		occupyPoint.push_back(json["occupyPoint"][i].asInt());
	}
	corps.clear();
	for (int i = 0; i < json["corps"].size(); i++){
		corps.push_back(json["corps"][i].asInt());
	}
}
Json::Value mapBlock::asJson() const{
	Json::Value result;
	result["type"] = type;
	
	Json::Value occupyPointArray;
	for (int i = 0; i < occupyPoint.size(); i++){
		occupyPointArray.append(occupyPoint[i]);
	}
	result["occupyPoint"] = occupyPointArray;
	result["owner"] = owner;
	result["TowerIndex"] = TowerIndex;
	
	Json::Value corpsArray;
	for (int i = 0; i < corps.size(); i++){
		corpsArray.append(corps[i]);
	}
	result["corps"] = corpsArray;
	return result;
}


Command::Command(Json::Value json){
	cmdType = commandType(json["cmdType"].asInt());
	
	parameters.clear();
	for (int i = 0; i < json["parameters"].size(); i++){
		parameters.push_back(json["parameters"][i].asInt());
	}
}
Json::Value Command::asJson() const{
	Json::Value result;
	result["cmdType"] = cmdType;
	Json::Value paramArray;
	for (int i = 0; i < parameters.size(); i++){
		paramArray.append(parameters[i]);
	}
	result["parameters"] = paramArray;
	return result;
}


CommandList::CommandList(Json::Value json){
	m_commands.clear();
	for (int i = 0; i < json.size(); i++){
		m_commands.push_back(Command(json[i]));
	}
}
Json::Value CommandList::asJson() const{
	Json::Value commandArray;
	for (int i = 0; i < m_commands.size(); i++){
		commandArray.append(m_commands[i].asJson());
	}
	return commandArray;
}


Info::Info(Json::Value json):
	totalPlayers(json["totalPlayers"].asInt()),
	playerAlive(json["playerAlive"].asInt()),
	totalRounds(json["totalRounds"].asInt()),
	totalTowers(json["totalTowers"].asInt()),
	totalCorps(json["totalCorps"].asInt()),
	myID(json["myID"].asInt()),
	myCommandList(json["myCommandList"])
{
	playerInfo.clear();
	for (int i = 0; i < json["playerInfo"].size(); i++){
		playerInfo.push_back(PlayerInfo(json["playerInfo"][i]));
	}

	towerInfo.clear();
	for (int i = 0; i < json["towerInfo"].size(); i++){
		towerInfo.push_back(TowerInfo(json["towerInfo"][i]));
	}

	corpsInfo.clear();
	for (int i = 0; i < json["corpsInfo"].size(); i++){
		corpsInfo.push_back(CorpsInfo(json["corpsInfo"][i]));
	}

	vector<vector<mapBlock>>* gameMapInfoArray = new vector<vector<mapBlock>>;
	for (int i = 0; i < json["gameMapInfo"].size(); i++){
		vector<mapBlock> gameMapInfoArrayInside;
		for (int j = 0; j < json["gameMapInfo"][i].size(); j++){
			gameMapInfoArrayInside.push_back(mapBlock(json["gameMapInfo"][i][j]));
		}
		gameMapInfoArray->push_back(gameMapInfoArrayInside);
	}
	gameMapInfo = gameMapInfoArray;
}
Json::Value Info::asJson() const{
	Json::Value result;
	result["totalPlayers"] = totalPlayers;
	result["playerAlive"] = playerAlive;
	result["totalRounds"] = totalRounds;
	result["totalTowers"] = totalTowers;
	result["totalCorps"] = totalCorps;
	result["myID"] = myID;
	result["myCommandList"] = myCommandList.asJson();
	

	Json::Value playerArray;
	for (int i = 0; i < playerInfo.size(); i++){
		playerArray.append(playerInfo[i].asJson());
	}
	result["playerInfo"] = playerArray;


	Json::Value towerArray;
	for (int i = 0; i < towerInfo.size(); i++){
		towerArray.append(towerInfo[i].asJson());
	}
	result["towerInfo"] = towerArray;
	

	Json::Value corpsArray;
	for (int i = 0; i < corpsInfo.size(); i++){
		corpsArray.append(corpsInfo[i].asJson());
	}
	result["corpsInfo"] = corpsArray;


	Json::Value gameMapArray;
	for (int i = 0; i < (*gameMapInfo).size(); i++){
		Json::Value gameMapArrayInside;
		for (int j = 0; j < (*gameMapInfo)[i].size(); j++){
			gameMapArrayInside.append(((*gameMapInfo)[i][j]).asJson());
		}
		gameMapArray.append(gameMapArrayInside);
	}
	result["gameMapInfo"] = gameMapArray;

	return result;
}