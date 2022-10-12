#pragma once
#ifndef DEFINITION_H
#define DEFINITION_H
#define FC15_DEBUG
#define NO_SILENT_MODE
#define NO_JSON
#define INF 100000000
#define TRANSITION -1   //���ɵ�������
#define PUBLIC 0      //������������
#define NOTOWER -1    //��ǰ����û�з�����
//#define NOTASK  -1    //��ǰ����������������
#define OUTOFRANGE -2  //��ǰ�����ڵ�ͼ֮��
//#define FC15_SAVEMODE
#define SAVETXT
//#define PAUSE
//#define NOTICE


#include <vector>
#include <string>
#include <initializer_list>
#include <stdexcept>
#include <map>
#include <set>
#include <iostream>
#include "../json/json.h"

using namespace std;
typedef int    TMovePoint;     //��FC18���ж���
typedef int    TBattlePoint;   //��FC18��ս����
typedef int    THealthPoint;   //��FC18������ֵ
typedef int    TBuildPoint;    //��FC18���Ͷ��������̽����������
typedef int    TProductPoint;  //��FC18������������
typedef int	   TExperPoint;    //��FC18�����ľ���ֵ
typedef int    TOccupyPoint;   //��FC18��������Χ����ʩ�ӵ�ռ������ֵ
typedef int    TIntPara;       //��FC18������ϵ��ֵ
typedef double TDoublePara;    //��FC18��˫���ȸ�����ϵ��ֵ
typedef int    TPlayer;        //��FC18����Ҹ���
typedef int    TTower;         //��FC18�����ĸ���
typedef int    TCorps;         //��FC18�����Ÿ���
typedef int    TPlayerID;      //��FC18�����ID��
typedef int    TTowerID;       //��FC18��������ID��
typedef int    TCorpsID;       //��FC18������ID��
typedef string TMapID;         //��FC18����ͼID��
typedef int    TMap;           //��FC18����ͼ�������߶�/��ȣ�
typedef int    TRound;         //��FC18���غ���
typedef int    TScore;         //��FC18����ҵ÷�
typedef int    TDist;          //��FC18����Ϸ�о���Ķ���
typedef int    TOperaNum;      //��FC18���������ĸ���
typedef int    TPosition;      //��FC18����Ϸ�ж�ά�����Ķ���
typedef double TLength;        //��FC18����Ϸ�г��ȵĶ���
typedef int    TLevel;         //��FC18���������Եȼ�


const int MAX_CORPS_LEVEL = 3;    //��FC18�����ı��ŵȼ�
const int MAX_TOWER_LEVEL = 8;    //��FC18�����ķ������ȼ�
const int TERRAIN_TYPE_NUM = 5;    //��FC18�����ε�������
const int BATTLE_CORPS_TYPE_NUM = 3;    //��FC18����ս���ŵ�������
const int CONSTRUCT_CORPS_TYPE_NUM = 2;    //��FC18�����̱��ŵ�������
const int TOWER_PRODUCT_TASK_NUM = 6;     //��FC18��������������������
const int TOWER_EXPER_GAIN_SCALE = 3;     //��FC18������ÿ�غϾ���ֵ���ӵȼ���
const int OCCUPY_POINT_DIST_SCALE = 5;    //��FC18��������Χ����ʩ��ռ������ֵ�ľ���ȼ��м���
const int CORPS_ACTION_TYPE_NUM = 10;    //��FC18�������ܽ��еĲ���������
const int TOWER_ACTION_TYPE_NUM = 3;     //��FC18�����������еĲ���������
const int MAX_ROUND = 300;               //��FC18����Ϸȫ�̵����غ�����ȷ���ģ�����FC15���ⲿ�ļ�����
const int TOWER_SCORE = 10;              //��FC18��������ҵ÷�ʱÿ��������ÿ���ȼ��÷�
const int BATTLE_CORP_SCORE = 2;         //��FC18��ս������ÿ���Ǽ��÷�
const int CONSTRUCT_CORP_SCORE = 4;      //��FC18�����̱���ÿ���÷�
const int KILL_SCORE = 5;                //��FC18����ɱ�֣�ռ����/��²����/��ɱ���ŵ÷�
const int CORP_SCORE = 4;                //��FC18���������ŵ÷�
const int MAX_CMD_NUM = 50;              //��FC18������ÿ�����ÿ�����������
const int MAX_TOWER_NUM = 10;            //��FC18���������������
const int MAX_BATTLE_NUM = 10;           //��FC18����������ս������Ŀ
const int MAX_CONSTRUCT_NUM = 10;        //��FC18�������󹤳̱�����Ŀ


class Crops;
struct CorpsInfo;
typedef vector<CorpsInfo>	CorpsInfoUnit; //��FC18��һ����Ԫ�������б�����Ϣ


//��FC18����ά�����ṹ��
struct TPoint
{
	TPosition  m_x;
	TPosition  m_y;
};

//��FC18�������������ݽṹ��
struct TowerConfig {
	int initBuildPoint;       //��ʼ������
	int initProductPoint;      //��ʼս����
	int initHealthPoint;      //��ʼ����ֵ
	int upgradeExper;         //������һ�����辭��ֵ
	int battleRegion;         //��������
};


//��FC18����������
enum corpsType
{
	Battle = 0,          //��ս����
	Construct = 1        //���̽������
};


//��FC18����ս���������ö����
enum battleCorpsType
{
	Warrior = 0,         //սʿ
	Archer = 1,         //������
	Cavalry = 2,         //���
};


//��FC18�����̽�����ŵ�ö����
enum constructCorpsType
{
	Builder = 0,           //������
	Extender = 1           //������
};




//��FC18����������
enum commandType {
	corpsCommand = 0,         //��������
	towerCommand = 1,         //����������
};


//��FC18�����Ų������ͣ�Cǰ׺��ʾCorps��
enum CorpsCommandEnum
{//                                                          ��ս����        ���̱���
	CMove = 0,       //�ڵ�ͼ���ƶ�                     ��              ��
	//CStation = 1,       //פ���ڵ�ͼ�������Լ�����       ��              ��
	CStationTower = 2,       //פ���������Լ�����������         ��              ��
	CAttackCorps = 3,       //�����Է������ı���               ��
	CAttackTower = 4,       //�����Է���������                 ��
	//CRegroup = 5,       //��������                         ��
	//CDissolve = 6,       //���Ž�ɢ                         ��              ��
	CBuild = 7,       //�޽��·�����                                     ��
	CRepair = 8,       //����ԭ������                                     ��
	CChangeTerrain = 9,       //�ı䷽�����                                     ��
};

//��FC18��������Json�еĴ���(J��ʾJson����)
enum CmdJsonNumber
{
	JMove = 0,
	JStation = 1,
	JStationTower = 2,
	JAttackCorps = 3,
	JAttackTower = 4,
	JRegroup = 5,
	JDissolve = 6,
	JBuild = 7,
	JRepair = 8,
	JChangeTerrain = 9,
	JProduct = 10,
	JTowerAttackCorps = 11,
	JTowerSttackTower = 12
};

//��FC18�������ƶ��ķ���
enum corpsMoveDir
{
	CUp = 0,         //�����ƶ�1��
	CDown = 1,         //�����ƶ�1��
	CLeft = 2,         //�����ƶ�1��
	CRight = 3          //�����ƶ�1��
};

//��FC18�����Ĳ������ͣ�Tǰ׺��ʾtower��
enum towerCommand
{
	TProduct = 0,       //��������
	TAttackCorps = 1,       //������������
	TAttackTower = 2        //����������
};


//��FC18�����������������ͣ�P��ʾproduct��
enum productType
{//                                           �����ر�
	PWarrior = 0,       //����սʿ           1star-սʿ
	PArcher = 1,       //����������         1star-������
	PCavalry = 2,       //������ʦ           1star-��ʦ
	PBuilder = 3,       //����������        1-�����߱���
	PExtender = 4,       //����������       1-�����߱���
	PUpgrade = 5,       //����������      ���ȼ�+1��max=8)
	NOTASK = -1
};


//��FC18�����ε�ö���ࣨTRǰ׺��ʾ���Σ�
enum terrainType
{
	TRTower = 0,       //��
	TRPlain = 1,       //ƽԭ
	TRMountain = 2,       //ɽ��
	TRForest = 3,       //ɭ��
	TRSwamp = 4,       //����
	TRRoad = 5,       //��·
	TRGate = 6,       //��У��
	TRHall = 7,       //������
	TRClassRoom1 = 8,  //�廪ѧ��x+z+
	TRClassRoom2 = 9,  //�廪ѧ��x-z+
	TRClassRoom3 = 10, //�廪ѧ��x-z-
	TRClassRoom4 = 11, //�廪ѧ��x+z-
	TRTHUEmpty = 12    //�廪Ԫ��ռ�ݵĿյ�
};


//��FC18����Ϸ���е�״̬
enum gameState
{
	Normal = 0,          //�������У����浵
	RecoverMap = 1,      //ֻ����ͼ�浵����ģʽ
	RecoverRound = 2,    //���غϣ�������ͼ���浵�ָ�ģʽ
};


//��FC18�����Ų�����
const string CorpsCmd[CORPS_ACTION_TYPE_NUM] =
{
	"move","station","station at tower","attack corps","attack tower","regroup","dissolve","build tower","repair tower","change terrain"
};

//��FC18����������
const string TowerCmd[TOWER_ACTION_TYPE_NUM] =
{
	"produce","attack corps","attack tower"
};

//��FC18��������������
const string ProductCmd[TOWER_PRODUCT_TASK_NUM] =
{
	"warrior","archer","caster","builder","extender","upgrade"
};

//��FC18���ƶ�������
const string Direction[4] =
{
	"up","down","left","right"
};

//��FC18���ı�ĵ�����
const string Terrain[TERRAIN_TYPE_NUM + 8] =
{
	"tower","plain","mountain","forest","swamp","road","erxiaomen","dalitang","qinghuaxuetang","qinghuaxuetang","qinghuaxuetang","qinghuaxuetang","THU"
};

//��FC18����ս��������
const string BattleName[3] =
{
	"warrior","archer","caster"
};

//��FC18�����̱�������
const string ConstructName[2] =
{
	"Builder","Explorer"
};

//��FC18����ս�����ж���������ս���ŵ�ö����������϶�Ӧ���ҿ����˵ȼ���
const TMovePoint battleMovePoint[BATTLE_CORPS_TYPE_NUM][MAX_CORPS_LEVEL] =
{
	{4,   4,   4},    //սʿ
	{4,   4,   4},    //������
	{8,   8,   8}     //��ʦ
};

//��FC18�����̱��ж�����������û�У��ȼ�����������
const TMovePoint constructMovePoint[CONSTRUCT_CORPS_TYPE_NUM] = { 4,4 };

//��FC18����ս���ų�ʼս����������ս���ŵ�ö����������϶�Ӧ���ҿ����˵ȼ���
const TBattlePoint corpsBattlePoint[BATTLE_CORPS_TYPE_NUM][MAX_CORPS_LEVEL] =
{
	{36,   44,   52},    //սʿ
	{30,   38,   46},    //������
	{44,   52,   60}     //��ʦ
};


//��FC18����ս���ŵ�ս��������ϵ��������ս���ŵ�ö����������϶�Ӧ���ҿ����˵ȼ���
const TIntPara corpsBattleGain[BATTLE_CORPS_TYPE_NUM][MAX_CORPS_LEVEL] =
{
	{2,   2,   2},    //սʿ
	{2,   2,   2},    //������
	{4,   4,   4}     //���
};


//��FC18����ս���ŵĹ���ϵ��������ս���ŵ�ö����������϶�Ӧ���ҿ����˵ȼ���
const TDoublePara corpsAttackTowerGain[BATTLE_CORPS_TYPE_NUM][MAX_CORPS_LEVEL] =
{
	{0.4,   0.4,   0.4},    //սʿ
	{0.7,   0.7,   0.7},    //������
	{0.5,   0.5,   0.5}     //���
};


//��FC18����ս���ų�ʼ����ֵ������ս���ŵ�ö����������϶�Ӧ���ҿ����˵ȼ���
const THealthPoint battleHealthPoint[BATTLE_CORPS_TYPE_NUM][MAX_CORPS_LEVEL] =
{
	{60,   80,   90},    //սʿ
	{50,   70,   90},    //������
	{70,   90,   110}    //���
};

//��FC18��ս��������̾��� սʿ1 ������2 ���1
const int TBattleRange[BATTLE_CORPS_TYPE_NUM] = { 1, 2, 1 };

//��FC18�����Ų�������������������ж�ָ��Ϸ��ԣ�����Ų�����ö����������϶�Ӧ)
const TOperaNum CorpsOperaNumNeed[CORPS_ACTION_TYPE_NUM] =
{
	3,    //�ƶ�
	2,    //פ��
	2,    //פ����
	3,    //��������
	3,    //������
	INF,  //�������ࣨȥ����
	INF,  //���Ž�ɢ��ȥ����
	2,    //�޽���
	2,    //ά����
	3     //�ĵ���
};


//��FC18�����̽�����Ų������Ͷ������ģ�����Ų�����ö����������϶�Ӧ)
const TBuildPoint constructBuildCost[CORPS_ACTION_TYPE_NUM] =
{
	0,       //�ڵ�ͼ���ƶ�
	0,       //פ���ڵ�ͼ�������Լ�����
	0,       //פ���������Լ�����������
	0,       //�����Է������ı���
	0,       //�����Է���������
	0,       //��������
	0,       //���Ž�ɢ
	0,       //�޽��·�����
	1,       //����ԭ������
	1,       //�ı䷽�����
};

const TOperaNum towerOperaNumNeed[TOWER_ACTION_TYPE_NUM] =
{
	3,       //��������
	3,       //����������
	3        //��������
};

//��FC18������������������������ֵ
const TProductPoint TowerProductCost[TOWER_PRODUCT_TASK_NUM] =
{//                                 �����ر�                                           ����˵��
	40,       //����սʿ         1star-սʿ
	60,       //����������      1star-������
	100,      //������ʦ         1star-��ʦ
	40,       //����������        1-�����߱���
	40,       //����������        1-�����߱���
	40        //����������      ���ȼ�+1��max=8)       ����40����Сֵ��ʵ��ֵΪִ�и�����ĵ�һ�غ����ĵȼ�*40��Ҫ����ʵ�������  
};


//��FC18��ÿ�غ����ľ���ֵ������غ����Ĺ�ϵ
//��GC18��ע��ʵ�ʷ��ʵ�ʱ�򣬴���غ���/100��ȡ����300�غϴ���2,301�غ�����3
//��FC18����ֱ�ӹ�ʽ���㣺5 + 5 * floor(currentRound / 100)��ע��߽�ֵҪ����Դ�
const TExperPoint TowerExperGain[TOWER_EXPER_GAIN_SCALE + 1] =
{//               �غ���
	5,//          [0,100)
	10,//         [100,200)
	15,//         [200,300]
	0//           (300,+��)
};


//��FC18��������Χ����ʩ�ӵ�ռ������ֵ�������Ĺ�ϵ��
const TOccupyPoint TowerOccupyPoint[OCCUPY_POINT_DIST_SCALE + 1] =
{//                ��������ľ���
	100,//              1��
	80,//               2��
	50,//               3��
	20,//               4��
	10,//               5��
	0//               6����Զ
};


//��FC18����ÿ���ȼ��ʼ��ʱ��������Ե�ֵ�����ڳ�ʼ������
const struct TowerConfig TowerInitConfig[MAX_TOWER_LEVEL] =
{
	{10,25,100,20, 2},
	{15,27,110,20, 2},
	{20,29,120,25, 2},
	{25,32,130,30, 2},
	{30,35,140,40, 2},
	{35,38,150,40, 2},
	{40,41,160,50, 2},
	{45,45,170,INF,2}
};


//��FC18���ж������ģ�����ε�ö����������϶�Ӧ��
const TMovePoint CorpsMoveCost[TERRAIN_TYPE_NUM + 8] =
{
	0,    //��
	2,    //ƽԭ
	4,    //ɽ��
	3,    //ɭ��
	4,    //����
	1,    //��·
	INF,  //��У��
	INF,  //������
	INF,  //�廪ѧ��1
	INF,  //�廪ѧ��2
	INF,  //�廪ѧ��3
	INF,  //�廪ѧ��4
	INF   //�廪Ԫ�ؿյ�
};


//��FC18��ս�������棨����ε�ö����������϶�Ӧ��
const TBattlePoint CorpsBattleGain[TERRAIN_TYPE_NUM + 8] =
{
	0,    //��
	0,    //ƽԭ
	5,    //ɽ��
	3,    //ɭ��
	-3,   //����
	0,    //��·
	0,    //��У��
	0,    //������
	0,    //�廪ѧ��1
	0,    //�廪ѧ��2
	0,    //�廪ѧ��3
	0,    //�廪ѧ��4
	0     //�廪Ԫ�ؿյ�
};

/*
//4���廪Ԫ�ع̶����Σ���Ӧ��ͬ������ģʽ
const terrainType attachTerrain0[3][4] =
{
	{TRClassCenter, TRClassSide, TRHall, TRPlain},
	{TRClassSide, TRPlain, TRPlain, TRPlain},
	{TRPlain, TRPlain, TRGate, TRForest}
};

const terrainType attachTerrain1[3][4] =
{
	{TRForest, TRGate, TRPlain, TRPlain},
	{TRPlain, TRPlain, TRClassCenter, TRClassSide},
	{TRPlain, TRHall, TRClassSide, TRPlain}
};

const terrainType attachTerrain2[4][3] =
{
	{TRPlain, TRClassCenter, TRClassSide},
	{TRPlain, TRClassSide, TRPlain},
	{TRGate, TRPlain, TRHall},
	{TRForest, TRPlain,TRPlain }
};

const terrainType attachTerrain3[4][3] =
{
	{TRPlain, TRPlain, TRForest},
	{TRHall, TRPlain, TRGate},
	{TRPlain, TRClassCenter, TRClassSide},
	{TRPlain, TRClassSide, TRPlain}
};
*/
//@@@��FC18���������ṹ�壬����Ҫ����Ϣ�ټ�

class TowerInfo {
public:
	TowerInfo(){};				// �չ��캯�� ���� swm_sxt
	TowerInfo(Json::Value);			// ��Json������ ���� swm_sxt
	Json::Value asJson() const;		//תΪJson���� ���� swm_sxt
	bool    exist;      //�������Ƿ����
	TTowerID      ID;   //������ID
	TPlayerID     ownerID;  //�������ID
	TPoint        position;    //λ��
	TProductPoint productPoint;  //������
	productType   pdtType;     //����һ����������ָ�����δ��ɵ��������ࣨ����һ������ָ����ɣ���Ϊ-1��
	TProductPoint productConsume;  //����һ����������ָ���δ��������ʣ��Ĺ�������
	TBattlePoint  battlePoint;   //ս����
	THealthPoint  healthPoint;   //����ֵ
	TLevel        level;       //�ȼ�
};


//@@@��FC18�����Žṹ�壬����Ҫ����Ϣ�ټ�
class CorpsInfo
{
public:
	CorpsInfo(){};				// �չ��캯�� ���� swm_sxt
	CorpsInfo(Json::Value);			// ��Json������ ���� swm_sxt
	Json::Value asJson() const;		//תΪJson���� ���� swm_sxt
	bool	exist;		//�Ƿ����
	TPoint	pos;		//��������
	TCorpsID		ID;	//����ID
	THealthPoint	HealthPoint;	//����ֵ
	TBuildPoint		BuildPoint;		//�Ͷ���
	TPlayerID		owner;			//�������ID
	corpsType       type;           //��������
	TMovePoint      movePoint;      //�ж���
	battleCorpsType		m_BattleType;	//ս������
	constructCorpsType	m_BuildType;	//�������
};


//@@@��FC18����ҽṹ��
class PlayerInfo
{
public:
	PlayerInfo(){};				// �չ��캯�� ���� swm_sxt
	PlayerInfo(Json::Value);		// ��Json������ ���� swm_sxt
	Json::Value asJson() const;		//תΪJson���� ���� swm_sxt
	TPlayerID id;                        //��FC18����ҵ���ţ���ע�������Ŵ�1��ʼ�����������������[ID-1]
	int rank;                            //��FC18����ѡ��������������ֱ���ɳ��ֻغ�����λ�Σ�|������߰��������÷ֺͱ��ŵ÷���������|��ͬ���ΰ���������ռ��������з�����������²�з����������μ���������|������ͬ�������������������
	bool alive;                          //��FC18������Ƿ񻹻���

	//@@@��FC18���������������ţ�����ԭ����set<TCellID> cells
	set<TTowerID> tower;


	//��FC18��������б��ŵ���ţ�����Ҳ��set�������ݽṹ���ڲ��������������������
	set<TCorpsID> corps; //���б���
};


//Info�Ĵ��������vector<vector<>> ������
class mapBlock                                 //��FC18����ͼ������
{
public:
	mapBlock(){};				// �չ��캯�� ���� swm_sxt
	mapBlock(Json::Value);			// ��Json������ ���� swm_sxt
	Json::Value asJson() const;		//תΪJson���� ���� swm_sxt
	terrainType type;                           //��FC18���ؿ����ͣ���ӦterrainTypeö����
	vector<int> occupyPoint;                    //��FC18������ҵ�ռ������ֵ����Ϊ������-1
	int owner;                                  //��FC18�����������ţ�-1Ϊ����TRANSITION��-2Ϊ����PUBLIC
	int TowerIndex;								//@@@��FC18��λ�ڸõ�Ԫ��������±꣬��Ӧdata���myTowers��û������ʱ��Ϊ-1
	vector<TCorpsID> corps;						//��λ�ñ���
};

//��FC18����ͼ��Ԫ����Ϣ�ṹ��
struct mapBlockInfo
{
	terrainType type;                           //��FC18���ؿ����ͣ���ӦterrainTypeö����
	int owner;                                  //��FC18�����������ţ�-1Ϊ����TRANSITION��-2Ϊ����PUBLIC
	vector<int> occupyPoint;                    //��FC18������ҵ�ռ������ֵ����Ϊ������-1
	TTowerID towerIndex;                        //��FC18����ͼ������Ϣ��NOTOWER��ʾû����
};


//������
class CommandList;
//������ѧ����
//��ά���������
TPoint operator-(const TPoint& p1, const TPoint& p2);
//����ŷʽ����
TLength getDistance(const TPoint& p1, const TPoint& p2);
//����FC18����������Χ�ľ��루FC18���룩
TDist getDist(const TPoint& p1, const TPoint& p2);
TDist getDist(const int p1_x, const int p1_y, const int p2_x, const int p2_y);
//����ָ����������������
int generateRanInt(int start, int end);
//�������´��ָ�
std::ostream& operator << (std::ostream& os, const CommandList& cl);

struct TBarrier
{
	TPoint m_beginPoint;
	TPoint m_endPoint;
};


//@@@��FC18����ͼ����
class BaseMap
{
public:
	void   setID(TMapID _id) { id = _id; }         //��FC18�����õ�ͼ�����
	TMap   getWidth()  const { return m_width; }   //��FC18����ȡ��ͼ���
	TMap   getHeigth() const { return m_height; }  //��FC18����ȡ��ͼ�߶�

	string             id;                         //��FC18����¼��ͼ��id����game��ֵ����init����ʹ�ã�ѡ���Ӧ���ļ�
	TMap               m_width;                    //��FC18����ͼ���
	TMap               m_height;                   //��FC18����ͼ�߶�

	//@@@��FC18���洢��ͼ�ϵ����з�������Ϣ��������Ԫ��Ϊ��������Ϣ�ṹ�壩�����Բ���vector<TPoint> m_studentPos
	vector<TPoint>     m_studentPos;               //ֻ�趨ϸ�������֮꣬����������佻��game

	//��FC18���洢��ͼ�ϵ����б�����Ϣ��������Ԫ��Ϊ������Ϣ�ṹ�壩�����Բ���vector<TPoint> m_studentPos
	//vector<CorpsInfoUnit>     m_corpsinfo;

	//@@@��FC18����ȡ��ͼ�ϵ����з�������Ϣ���������Բ���const  vector<TPoint>& getStudentPos() const
	//@@@��FC18������һ����������Ϣ�ṹ���vector���ã������ⲿ�����޸�
	const  vector<TPoint>& getStudentPos() const { return m_studentPos; }

	//��FC18����ȡ��ͼ�ϵ����б�����Ϣ���������Բ���const  vector<TPoint>& getStudentPos() const
	//��FC18������һ��������Ϣ�ṹ���vector���ã������ⲿ�����޸�
	//const  vector<CorpsInfoUnit>& getCropsInfo() const { return m_corpsinfo; }

	bool   isPosValid(TPoint p) { return isPosValid(p.m_x, p.m_y); }             //�жϵ��Ƿ�Խ��
	bool   isPosValid(int x, int y) { return x >= 0 && x < m_width && y >= 0 && y < m_height; }
	//protected:
private:
	int cross(const TPoint& p1, const TPoint& p2) { return p1.m_x * p2.m_y - p1.m_y * p2.m_x; }//���
	int min(int a, int b) { return a < b ? a : b; }
	int max(int a, int b) { return a < b ? b : a; }
};

//��������
enum CommandType
{
	upgrade          //��������
	, changeStrategy //�ı�ϸ������
	, addTentacle    //��Ӵ���
	, cutTentacle    //�жϴ���
};

//��FC18���������������Ϣ
class Command
{
public:
	Command(Json::Value);			// ��Json������ ���� swm_sxt
	Json::Value asJson() const;		//תΪJson���� ���� swm_sxt
	Command(commandType _FC18type, initializer_list<int> _FC18parameters) :  //��FC18���ɳ�ʼ���б���Ĺ��캯��
		cmdType(_FC18type), parameters(_FC18parameters) {}
	Command(commandType _FC18type, vector<int> _FC18parameters) :            //��FC18����Ĭ���������鹹��Ĺ��캯��
		cmdType(_FC18type), parameters(_FC18parameters) {}
	Command() {}                                                             //��FC18��ָ�����������
	commandType cmdType;                                                     //��FC18����������
	vector<int> parameters;                                                  //��FC18��������ע�����в��������ͣ�
};

//��FC18�������б�
class CommandList
{
public:
	CommandList(){};				// �չ��캯�� ���� swm_sxt
	CommandList(Json::Value);			// ��Json������ ���� swm_sxt
	Json::Value asJson() const;			//תΪJson���� ���� swm_sxt
	void addCommand(commandType _FC18type, initializer_list<int> _FC18parameters)  //��FC18���ɳ�ʼ���б�ֱ���������
	{
		if (size() >= MAX_CMD_NUM) return;
		m_commands.emplace_back(_FC18type, _FC18parameters);
	}
	void addCommand(commandType _FC18type, vector<int> _FC18parameters)            //��FC18����Ĭ������������������Ҫ�������죩
	{
		if (size() >= MAX_CMD_NUM) return;
		Command newCmd;
		newCmd.cmdType = _FC18type;
		newCmd.parameters = _FC18parameters;
		m_commands.push_back(newCmd);
	}
	void removeCommand(int n)                                                      //��FC18���Ƴ���n������
	{
		if (n < 0 || n >= size())
			throw std::out_of_range("�Ƴ�����ʱԽ�� ");
		m_commands.erase(m_commands.begin() + n);
	}
	vector<Command> getCommand() { return m_commands; }                            //��FC18����ȡ��������
	Command& operator[](int n)                                                     //��FC18�����ʵ�n��������ظ����������
	{
		if (n < 0 || size() <= n)
			throw std::out_of_range("��������ʱԽ�� ");
		return m_commands[n];
	}
	int size() const { return int(m_commands.size()); }                            //��FC18����ȡ�ܹ�����������
	vector<Command>::iterator begin() { return m_commands.begin(); }               //��FC18�����ص�һ������ĵ�����
	vector<Command>::iterator end() { return m_commands.end(); }                   //��FC18���������һ������ĵ�����
	vector<Command>::const_iterator  begin() const { return m_commands.cbegin(); } //��FC18�����ص�һ������ĳ���������
	vector<Command>::const_iterator end() const { return m_commands.cend(); }      //��FC18���������һ������ĳ���������

private:
	vector<Command> m_commands;                                                    //��FC18��ָ�vector�洢
};


//@@@��FC18����������ҹ����ϵĸ�����Ϣ
class Info
{
public:
	Info(){};				// �չ��캯�� ���� swm_sxt
	Info(Json::Value);			// ��Json������ ���� swm_sxt
	Json::Value asJson() const;			//תΪJson���� ���� swm_sxt
	TPlayer totalPlayers;                                   //��FC18�����������4�ˣ�                               
	TPlayer playerAlive;                                    //��FC18��ʣ��������������ŵģ�
	TRound totalRounds;                                     //��FC18����ǰ�غ�����4���������ִ��һ�β���Ϊ1�غϣ�UI����1�����ִ�в�����1�غϣ�
	TTower totalTowers;                                     //��FC18�������ܵķ���������
	TCorps totalCorps;                                      //��FC18�������ܵı��Ÿ���
	TPlayerID myID;                                         //��FC18��ѡ��ID�ţ�ע����Ϸ�����ID���Ǵ�1��ʼ������ʱ����[myID - 1]���ָ�ʽ

	CommandList myCommandList;                              //��FC18�����ڽ�����ҷ�����ָ���ָ�

	//@@@��FC18����������������Ϣ��vector�����Բ���ԭ����vector<PlayerInfo> playerInfo;
	vector<PlayerInfo> playerInfo;   //������Ϣ

	//@@@��FC18���������з�������Ϣ��vector�����Բ���ԭ����vector<CellInfo> cellInfo;
	vector<TowerInfo> towerInfo;

	//@@@��FC18���������б�����Ϣ��vector�����Բ���ԭ����vector<vector<TentacleInfo> > tentacleInfo;
	//vector<vector<CorpsInfoUnit>> corpsInfo;//�±�Ϊij��λ�ñ�ʾλ��Ϊx:i,y:j�ı�����Ϣ
	vector<CorpsInfo> corpsInfo;

	//��FC18����ͼ��Ϣ
	//vector<vector<mapBlockInfo>> mapInfo;
	//������ͼʱ ����һάΪy���꣬�ڶ�άΪx���꣬��gameMapInfo[y][x]��ʾ��x,y����ĵ�ͼ��Ϣ
	const vector<vector<mapBlock>>* gameMapInfo;

};

#endif // DEFINITION_H




