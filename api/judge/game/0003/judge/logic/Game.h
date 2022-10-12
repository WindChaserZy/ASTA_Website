#ifndef GAME_H_
#define GAME_H_
#include "Field.h"
#include "Camp.h"
#include "CommandList.h"
//Âß¼­Àà
#ifdef _DEBUG

#define new  new(_NORMAL_BLOCK, __FILE__, __LINE__)

#endif
class Game {
private:
    PlantCamp* PCamp;
    ZombieCamp* ZCamp;
public:
    Game(field* _Field) {
        Field = _Field;
        PCamp = nullptr;
        ZCamp = nullptr;
        time = 0;
        index = 1;
    }
    ~Game() {
        
    }
    void setField(field* _field)
    {
        Field = _field;
    }
    Camp* GetPlantCamp() {
        if (PCamp == nullptr)
            PCamp = new PlantCamp(Field, 400);
        return PCamp;
    }
    Camp* GetZombieCamp() {
        if (ZCamp == nullptr)
            ZCamp = new ZombieCamp(Field, 300);
        return ZCamp;
    }
    static int ImproveHP() {
        if (time < 1000)
            return 0;
        return (time - 1000);
    }
    static int ImproveDPS() {
        if (time < 1000)
            return 0;
        return (time - 1000);
    }
    static void AddTime() {
        time++;
    }
    static unsigned int getTime() {
        return time;
    }
    void restart() {
        time = 0;
        PCamp = nullptr;
        ZCamp = nullptr;
        Field = nullptr;
        index = 1;
    }
    static unsigned int index;
    field* Field;
    static unsigned int time;
    vector<vector<int>> new_Plants;
    vector<vector<int>> new_Zombies;
    vector<vector<int>> removed_plants;
};

#endif