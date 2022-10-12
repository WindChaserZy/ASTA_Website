#ifndef CAMP_H_
#define CAMP_H_
#include "Interface.h"
#include <vector>
using std::vector;
#include "Plants.h"
#include "Zombies.h"
class field;
#ifdef _DEBUG

#define new  new(_NORMAL_BLOCK, __FILE__, __LINE__)

#endif
class Camp:public ICamp{
private:
protected:
    int sun; // ����
    field* Field; //����ָ��
    int** currentPlants;
    int*** currentZombies;
    int* leftLines;
public:
    
    Camp() = delete;
    Camp(const Camp& _Camp) = delete;
    Camp(field* _Field, int _sun = 300);
    // ����ͬһ��field����ɾ��Ĭ�Ϻ���
    int getSun() { return sun; } //�õ�����
    virtual int getCurrentType() = 0;
    virtual int* getPlantCD() = 0;
    int** getCurrentPlants();
	int*** getCurrentZombies();
    int* getLeftLines();
    int getRows();
    int getColumns();
    void setSun(int _sun);
    void addSun(int _sun);
    void setCamp(field* Field)
    {
        this->Field = Field;
    }
    virtual ~Camp();

};
class PlantCamp :public Camp {
private:
    vector<int>LastPlacePlant;
    vector<int> PlantCD;
    int* NowCD;
public:
    PlantCamp() = delete;
    PlantCamp(const PlantCamp& _PlantCamp) = delete;
    PlantCamp(field* _field, int _sun = 400);
    int getCurrentType() {
        return 0;
    }
    bool PlacePlant(int x, int y, int type);
    bool RemovePlant(int x, int y);
    int* getPlantCD();
    ~PlantCamp()
    {
        delete[] NowCD;
    }
};
class ZombieCamp :public Camp {
private:
    
    vector<int> PlantCD;
    int* NowCD;
public:
    vector<int>LastPlaceZombie;
    ZombieCamp() = delete;
    ZombieCamp(const ZombieCamp& ZombieCamp) = delete;
    ZombieCamp(field* _field, int _sun = 300);
    int getCurrentType()
    {
        return 1;
    }
    bool PlaceZombie(int y, int type);
    int* getPlantCD();
    ~ZombieCamp()
    {
        delete[] NowCD;
    }
};
#endif