#ifndef MAP_H_
#define MAP_H_

#include <string>
#include <vector>
#include "definition.h"
#include <math.h>
#include <cmath>
#include <ctime>
#define UNALLOCATED -1   //δ�������

using namespace std;
namespace DATA 
{
	struct Data;
}

const terrainType terrain[TERRAIN_TYPE_NUM + 1] =     //��FC18�����Σ���ռ�������С���������ε����㣬������������
{//                  enumֵ   ����
    TRPlain,       //    1       1
    TRRoad,        //    5       2
    TRMountain,    //    2       3
    TRForest,      //    3       4
    TRSwamp,       //    4       5
    TRTower        //    0       6
};

const TPoint paraOffset[8] =                                //��FC18���������������ͼʱ��ǿ��ͨ��
{
    {1 , 0},
    {1 , 1},
    {0 , 1},
    {-1, 1},
    {-1, 0},
    {-1,-1},
    {0 ,-1},
    {1 ,-1}
};




class Map:public BaseMap
{
public:
	Map():data(nullptr){}                       //��FC18��map��Ĭ�Ϲ��캯��
    ~Map() { clearAll(); }                      //��FC18�������������ͷű�����Դ
	DATA::Data* getData(){ return data; }       //��FC18��mapҲ���Է���ȫԱ�����Data
	void setData(DATA::Data* d) { data = d; }   //��FC18��mapҲ�����޸�ȫԱ�����Data
	vector<vector<mapBlock>> map;               //��FC18����Ϸ��ʵ�ʴ洢�ĵ�ͼ
	//~Map();
	bool randomInitMap(ofstream& cmdF,ofstream& infoF);                          //��FC18���������һ����ͼ�������������趨��ʼ����λ��
    bool readMap(ifstream& inMap, ofstream& cmdF, ofstream& infoF,bool enableOutput, vector<string> players_name, string log_path);   //ͨ���ļ���ʼ����ͼ��Ϣ�����������ͼ���ݺͳ�ʼ���������
	void saveMapJson();                       //��FC18�������ͼ��json����
    mapBlockInfo ShowInfo(int x,int y);                       //��FC18�����ɵ�ͼ������Ϣ
    void modifyOccupyPoint(TPlayerID oldOwner, TPlayerID newOwner, TPoint p);       //��FC18�������������߸ı��޸���Χ�����ռ������ֵ
    bool withinMap(TPoint p);                    //��FC18���ж�p���Ƿ��ڵ�ͼ֮��
    TPlayerID ownerChange(TPoint p);             //��FC18����顢�ı䷽��pλ�õ�ӵ����
    TPlayerID showOwner(TPoint p);               //��FC18���жϵ�ǰ����ӵ���ߵ�ID
    void setReadPath(string readPath) { read_path = readPath; }   //��FC18��������Ϸ�浵·��
    void clearAll();                        //��FC18����new����������corps��delete����Ҳ������player��delete��
    void saveMap();                         //��FC18����������Ϸ�����ͼ����
    bool recoverFromMap(vector<pair<TPoint, TPoint>>& towerPoint);                  //��FC18���ӵ�ͼ�浵�ָ�

private:
	DATA::Data* data;                            //��FC18��������Ϸ�е����ݴ���
    string log_path;                             //��FC18������ļ���·��
    string read_path;                            //��FC18�����ڶ���浵��·��
};


class Perlin {                                                        //��FC18���������������ͼ������
public:
    float persistence;
    int Number_Of_Octaves;

    Perlin() {
        srand(unsigned(time(0)));
        persistence = 0.0001;
        Number_Of_Octaves = 3;
        iterRound = 1;
        connectStandard = 5;
    }
    ~Perlin(){}

    double random(double start, double end)
    {
        return start + (end - start) * rand() / (RAND_MAX + 1.0);
    }

    double Noise(int x, int y)    // ����(x,y)��ȡһ����������ֵ
    {
        int n = x + y * int(random(53, 57));
        n = (n << 13) ^ n;
        return (1.0 - ((n * (n * n * int(random(16000, 17000)) + int(random(830000, 870000))) + int(random(1300000000, 1700000000))) & 0x7fffffff) / 1073741824.0);
    }

    double SmoothedNoise(int x, int y)   //�⻬����
    {
        double corners = (Noise(x - 1, y - 1) + Noise(x + 1, y - 1) + Noise(x - 1, y + 1) + Noise(x + 1, y + 1)) / 16;
        double sides = (Noise(x - 1, y) + Noise(x + 1, y) + Noise(x, y - 1) + Noise(x, y + 1)) / 8;
        double center = Noise(x, y) / 4;
        return corners + sides + center;
    }

    double Cosine_Interpolate(double a, double b, double x)  // ���Ҳ�ֵ
    {
        double ft = x * 3.1415927;
        double f = (1 - cos(ft)) * 0.5;
        return a * (1 - f) + b * f;
    }

    double Linear_Interpolate(double a, double b, double x) //���Բ�ֵ
    {
        return a * (1 - x) + b * x;
    }

    double InterpolatedNoise(float x, float y)   // ��ȡ��ֵ����
    {
        int integer_X = int(x);
        float  fractional_X = x - integer_X;
        int integer_Y = int(y);
        float fractional_Y = y - integer_Y;
        double v1 = SmoothedNoise(integer_X, integer_Y);
        double v2 = SmoothedNoise(integer_X + 1, integer_Y);
        double v3 = SmoothedNoise(integer_X, integer_Y + 1);
        double v4 = SmoothedNoise(integer_X + 1, integer_Y + 1);
        double i1 = Cosine_Interpolate(v1, v2, fractional_X);
        double i2 = Cosine_Interpolate(v3, v4, fractional_X);
        return Cosine_Interpolate(i1, i2, fractional_Y);
    }

    double PerlinNoise(float x, float y)    // ���յ��ã�����(x,y)������Ӧ��PerlinNoiseֵ
    {
        double noise = 0;
        double p = persistence;
        int n = Number_Of_Octaves;
        for (int i = 0; i < n; i++)
        {
            double frequency = pow(2, i);
            double amplitude = pow(p, i);
            noise = noise + InterpolatedNoise(x * frequency, y * frequency) * amplitude;
        }

        return noise;
    }

    friend class Map;
private:
    int iterRound;
    int connectStandard;
};

#endif //_MAP_H_
