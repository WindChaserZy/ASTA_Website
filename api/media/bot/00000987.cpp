#include "ai.h"
#include <iostream>
#include <vector>
#include "Interface.h"
#include <queue>
using namespace std;
//植物种类
enum PlantType
{
    NOPLANT = 0,
    SUNFLOWER,
    WINTERPEASHOOTER,
    PEASHOOTER,
    SMALLNUT,
    PEPPER,
    SQUASH
};
//僵尸种类
enum ZombieType
{
    NOZOMBIE = 0,
    NORMAL,
    BUCKET,
    POLEVAULT,
    SLED,
    GARGANTUAR
};
const int plantCost[7] = {0, 50, 400, 100, 50, 125, 50},
          plantCd[7] = {0, 10, 30, 10, 40, 60, 60},
          zombieCost[6] = {0, 50, 125, 125, 300, 300},
          zombieCd[6] = {0, 15, 20, 20, 25, 25},
          plantHp[7] = {0, 300, 300, 300, 4000, 114514, 114514},
          plantDps[7] = {0, 0, 20, 10, 0, 1800, 1800},
          zombieDps[6] = {0, 75, 75, 75, 114514, 114514};
int zombieHp[6] = {0, 270, 820, 200, 1600, 3000};
struct Sunflower
{
    int row, column, cd;
    Sunflower(int Row, int Column)
    {
        cd = 24;
        row = Row, column = Column;
    }
}; //跟踪向日葵
int *zombieNum(int ***zombies)
{
    int cnt[7] = {}, *p = cnt;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 10; j++)
            for (int k = 0; k < 10; k++)
            {
                if (zombies[i][j][k] = -1)
                    break;
                else
                    cnt[zombies[i][j][k]]++;
            }
    return p;
} //将zombies分类计数
int *zombieNum(int zombies[5][10][10])
{
    int cnt[7] = {}, *p = cnt;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 10; j++)
            for (int k = 0; k < 10; k++)
            {
                if (zombies[i][j][k] = -1)
                    break;
                else
                    cnt[zombies[i][j][k]]++;
            }
    return p;
} //重载
struct Zombie
{
    int num;
    int hp;
    int coX, coY;
    int index; // index为时间戳
    Zombie(int Num, int row)
    {
        coX = row, coY = 9;
        hp = zombieHp[Num];
        num = Num;
    }
    // int speed;   ?
};
struct Plant
{
    int num;
    int hp;
    int coX, coY;
    int dps;
    Plant(int Num, int row, int col)
    {
        num = Num;
        coX = row, coY = col;
        hp = plantHp[Num];
        dps = plantDps[Num];
    }
};
struct Actionlist
{
    int plantPlace[5][10] = {}, zombiePlace[5] = {};
    int plantRemove[5][10] = {};
};
class Game
{
public:
    int time, sun, moon;
    int plants[5][10], zombies[5][10][10];
    int cdPlant[7], cdZombie[6];     //记录双方在当前tick下冷却
    int dps[5];                      //记录每行dps
    int flagPlant[7], flagZombie[6]; //记录冷却是否(1/0)完成
    int flagShovel[5][10];           //记录某个位置是否(1/0)进行铲除操作
    int zombieCostPerRow[5];
    vector<Sunflower> sunFlowers;
    vector<Plant> vectorPlants;
    vector<Zombie> vectorZombies;
    void plantremove(int i, int j, IPlayer *player)
    {
        player->removePlant(i, j);
        flagShovel[i][j] = 1;
    }
    void maintain(IPlayer *player)
    {
        time++;
        int **Plants = player->Camp->getCurrentPlants();    // currentPlants
        int ***Zombies = player->Camp->getCurrentZombies(); // currentZombies
        moon += int(time / 200.0) + 1;
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 10; j++)
            {
                if (plants[i][j] > Plants[i][j] && plants[i][j] != PEPPER && plants[i][j] != SQUASH)
                {
                    if (flagShovel[i][j] == 1)
                    {
                        flagShovel[i][j] = 0;
                    }
                    else
                    {
                        int num = plants[i][j];
                        moon += plantCost[num] / 5 + int(sqrt(plantHp[num]));
                        dps[i] -= plantDps[num];
                        if (num == 1)
                        {
                            for (int k = 0; k < sunFlowers.size(); k++)
                                if (sunFlowers[k].row == i && sunFlowers[k].column == j)
                                {
                                    sunFlowers.erase(sunFlowers.begin() + k);
                                    break;
                                }
                        }
                    }
                } //植物阵亡
                else if (plants[i][j] < Plants[i][j])
                {
                    int num = Plants[i][j];
                    sun -= plantCost[num];
                    dps[i] += plantDps[num];
                    cdPlant[num] = plantCd[num];
                    flagPlant[num] = 0;
                    if (num == 1)
                    {
                        sun += 25;
                        sunFlowers.push_back(Sunflower(i, j));
                    }
                    vectorPlants.push_back(Plant(Plants[i][j], i, j));
                } //植物种植
                plants[i][j] = Plants[i][j];
                int flag = 0;
                for (int k = 0; k < vectorPlants.size(); k++)
                {
                    if (vectorPlants[k].coX == i && vectorPlants[k].coY == j)
                    {
                        if (vectorPlants[k].num != Plants[i][j])
                        {
                            vectorPlants.erase(vectorPlants.begin() + k);
                            k--;
                            if (Plants[i][j] != 0)
                                vectorPlants.push_back(Plant(Plants[i][j], i, j));
                        }
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0 && Plants[i][j] != 0)
                    vectorPlants.push_back(Plant(Plants[i][j], i, j));
            }
        int *z = zombieNum(zombies), *Z = zombieNum(Zombies);
        for (int i = 0; i < 5; i++)
        {
            int rowZombie[6] = {}, RowZombie[6] = {}; //前者为保存的状态，后者为当前状态
            for (int j = 0; j < 10; j++)
                for (int k = 0; k < 10; k++)
                {
                    if (zombies[i][j][k] = -1)
                        break;
                    else
                        rowZombie[zombies[i][j][k]]++;
                }
            for (int j = 0; j < 10; j++)
                for (int k = 0; k < 10; k++)
                {
                    if (Zombies[i][j][k] = -1)
                        break;
                    else
                        RowZombie[Zombies[i][j][k]]++;
                    ;
                }
            for (int j = 0; j < 6; j++)
                if (RowZombie[j] > rowZombie[j])
                    zombieCostPerRow[i] += zombieCost[j];
        }
        for (int i = 0; i < 7; i++)
        {
            if (z[i] < Z[i])
            {

            } // zombie die
            else if (z[i] > Z[i])
            {
                moon -= zombieCost[i];
                cdZombie[i] = zombieCd[i];
                flagZombie[i] = 0;
            } // zombie placed
        }

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                int k = 0;
                while (Zombies[i][j][k] != -1)
                {
                    zombies[i][j][k] = Zombies[i][j][k];
                    k++;
                    int flag = 0;
                    for (int l = 0; l < vectorZombies.size(); l++)
                        if (vectorZombies[l].num == Zombies[i][j][k] && vectorZombies[l].coY - j <= 1)
                            flag = 1;
                    if (flag == 0)
                    {
                        vectorZombies.push_back(Zombie(Zombies[i][j][k], i));
                        vectorZombies[vectorZombies.size() - 1].index = time;
                    }
                }
            }
        }

        vector<int> have_erased;
        for (int i = 0; i < vectorZombies.size(); i++)
        {
            int have_erased_flag = 0;
            for (int z = 0; z < have_erased.size(); z += 2)
            {
                if (vectorZombies[i].coX == have_erased[z] && vectorZombies[i].coY == have_erased[z + 1])
                {
                    have_erased_flag = 1;
                    break;
                }
            }

            if (Plants[vectorZombies[i].coX][vectorZombies[i].coY] != SMALLNUT || have_erased_flag == 1)
            {
                continue;
            }
            else
            {
                int num = vectorZombies[i].num;
                int original_num_of_this_kind = 0, now_num_of_this_kind = 0;
                int k = 0;
                while (zombies[vectorZombies[i].coX][vectorZombies[i].coY][k] != -1)
                {
                    if (zombies[vectorZombies[i].coX][vectorZombies[i].coY][k] == num)
                    {
                        original_num_of_this_kind++;
                    }
                    k++;
                }
                k = 0;
                while (Zombies[vectorZombies[i].coX][vectorZombies[i].coY][k] != -1)
                {
                    if (Zombies[vectorZombies[i].coX][vectorZombies[i].coY][k] == num)
                    {
                        now_num_of_this_kind++;
                    }
                    k++;
                }
                if (original_num_of_this_kind - now_num_of_this_kind > 0)
                {
                    vector<int> serialNum;
                    for (int j = 0; j < vectorZombies.size(); j++)
                    {
                        if (vectorZombies[j].num == num && vectorZombies[i].coY == vectorZombies[j].coY && vectorZombies[i].coX == vectorZombies[j].coX)
                        {
                            serialNum.push_back(j);
                        }
                    }
                    if (now_num_of_this_kind == 0)
                    {
                        for (int i = serialNum.size() - 1; i >= 0; i--)
                        {
                            vectorZombies.erase(serialNum[i] + vectorZombies.begin());
                        }
                    }
                    if (original_num_of_this_kind - now_num_of_this_kind == 1)
                    { // find the smallest hp
                        int small_hp = 5000, small_hp_num = 0;
                        for (int k = 0; k < serialNum.size(); k++)
                        {
                            if (small_hp > vectorZombies[serialNum[k]].hp)
                            {
                                small_hp = vectorZombies[serialNum[k]].hp;
                                small_hp_num = k;
                            }
                        }
                        vectorZombies.erase(small_hp_num + vectorZombies.begin());
                    }

                    have_erased.push_back(vectorZombies[i].coX);
                    have_erased.push_back(vectorZombies[i].coY);
                }
            }
        }
        for (int i = 0; i < vectorZombies.size(); i++)
        {
            int num = vectorZombies[i].num;
            int k = 0;
            int flag_self = 0;
            int flag_near = 0;
            while (Zombies[vectorZombies[i].coX][vectorZombies[i].coY][k] != -1)
            {
                if (num == Zombies[vectorZombies[i].coX][vectorZombies[i].coY][k])
                {
                    break;
                }
                else
                {
                    flag_self = 1;
                }
            }
            k = 0;
            while (Zombies[vectorZombies[i].coX][vectorZombies[i].coY - 1][k] != -1)
            {
                if (num == Zombies[vectorZombies[i].coX][vectorZombies[i].coY][k])
                {
                    vectorZombies[i].coY--;
                }
                else
                {
                    flag_near = 1;
                }
            }
            if (flag_self == 1 && flag_near == 1)
            {
                vectorZombies.erase(vectorZombies.begin() + i);
                i--;
            }
        }

        for (int i = 0; i < 7; i++)
        {
            if (cdPlant[i] > 0)
                cdPlant[i]--;
            if (cdPlant[i] == 0)
                flagPlant[i] = 1;
        }

        for (int i = 0; i < 6; i++)
        {
            if (cdZombie[i] > 0)
                cdZombie[i]--;
            if (cdZombie[i] == 0)
                flagZombie[i] = 1;
        }
        for (int i = 0; i < sunFlowers.size(); i++)
        {
            if (sunFlowers[i].cd > 0)
                sunFlowers[i].cd--;
            if (sunFlowers[i].cd == 0)
            {
                sun += 25;
                sunFlowers[i].cd = 24;
            }
        }

    } //将上一tick的状态转移至当前tick
    Game()
    {
        time = 0;
        sun = 400, moon = 300;
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 10; j++)
                plants[i][j] = 0, flagShovel[i][j] = 0;
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 10; j++)
                for (int k = 0; k < 10; k++)
                    zombies[i][j][k] = 0;
        for (int i = 0; i < 5; i++)
            dps[i] = 0, zombieCostPerRow[i] = 0;
        for (int i = 0; i < 7; i++)
            cdPlant[i] = 0, flagPlant[i] = 1;
        for (int i = 0; i < 6; i++)
            cdZombie[i] = 0, flagZombie[i] = 1;
    }                                              // initialize
    Game tranState(Actionlist q, IPlayer *player); //推算一系列操作q后状态
};                                                 // global status
Game Game::tranState(Actionlist q, IPlayer *player)
{
    Game newGame;
    {
        newGame.time = this->time, newGame.sun = this->sun, newGame.moon = this->moon;
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 10; j++)
                newGame.plants[i][j] = this->plants[i][j], flagShovel[i][j] = this->flagShovel[i][j];
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 10; j++)
                for (int k = 0; k < 10; k++)
                    newGame.zombies[i][j][k] = this->zombies[i][j][k];
        for (int i = 0; i < 7; i++)
            newGame.cdPlant[i] = this->cdPlant[i], newGame.flagPlant[i] = this->flagPlant[i];
        for (int i = 0; i < 6; i++)
            newGame.cdZombie[i] = this->cdZombie[i], newGame.flagZombie[i] = this->flagZombie[i];
        for (int i = 0; i < 5; i++)
            newGame.dps[i] = this->dps[i], newGame.zombieCostPerRow[i] = this->zombieCostPerRow[i];
    }
    // newGame=Game
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 10; j++)
        {
            if (q.plantPlace[i][j] > 0)
            {
                int num = q.plantPlace[i][j];
                newGame.sun -= plantCost[num];
                newGame.cdPlant[num] = plantCd[num];
                newGame.flagPlant[num] = 0;
                newGame.dps[i] += plantDps[num];
                newGame.plants[i][j] = num;
                newGame.vectorPlants.push_back(Plant(num, i, j));
            }
            //种植植物
            if (q.zombiePlace[i] > 0)
            {
                int num = q.zombiePlace[i];
                newGame.moon -= zombieCost[num];
                newGame.cdZombie[num] = zombieCd[num];
                newGame.flagZombie[num] = 0;
                newGame.vectorZombies.push_back(Zombie(num, i));
                newGame.vectorZombies[newGame.vectorZombies.size() - 1].index = time;
            }
            //放置僵尸
            if (q.plantRemove[i][j] > 0)
            {
                int k = 0;
                while (k < newGame.vectorPlants.size() && (newGame.vectorPlants[k].coX != i || newGame.vectorPlants[k].coY != j))
                    k++;
                newGame.vectorPlants.erase(newGame.vectorPlants.begin() + k);
            }
            //铲除植物
        }
    //放置操作
    vector<Plant> vectorRowPlants[5];
    vector<Zombie> vectorRowZombies[5];
    for (int i = 0; i < vectorPlants.size(); i++)
        vectorRowPlants[vectorPlants[i].coX].push_back(vectorPlants[i]);
    for (int i = 0; i < vectorZombies.size(); i++)
        vectorRowZombies[vectorZombies[i].coX].push_back(vectorZombies[i]);
    for (int i = 0; i < 5; i++)
    {

        int headPlantNum = -1, headZombieNum = -1;
        int headPlantCol = -1, headZombieCol = 10;
        int headZombieIndex = 1e9;
        for (int j = 0; j < vectorRowPlants[i].size(); j++)
        {
            if (vectorRowPlants[i][j].coY > headPlantCol)
            {
                headPlantCol = vectorRowPlants[i][j].coY;
                headPlantNum = j;
            }
        }
        for (int j = 0; j < vectorRowZombies[i].size(); j++)
        {
            if (vectorRowZombies[i][j].coY < headZombieCol || (vectorRowZombies[i][j].coY == headZombieCol && vectorRowZombies[i][j].index < headZombieIndex))
            {
                headZombieCol = vectorRowZombies[i][j].coY;
                headZombieNum = j;
                headZombieIndex = vectorRowZombies[i][j].index;
            }
        }
        //求解僵尸方head与植物方head
        for (int j = 0; j < vectorRowPlants[i].size(); j++)
        {
            int num = vectorRowPlants[i][j].num;
            switch (num)
            {
            case SUNFLOWER:
                break;
            case PEASHOOTER:
                vectorRowZombies[i][headZombieNum].hp -= plantDps[PEASHOOTER];
                break;
            case WINTERPEASHOOTER:
                for (int k = 0; k < vectorRowZombies[i].size(); k++)
                    if (vectorRowZombies[i][k].coY == headZombieCol)
                        vectorRowZombies[i][k].hp -= plantDps[WINTERPEASHOOTER];
                break;
            case SMALLNUT:
                break;
            case SQUASH:
                if (vectorRowPlants[i][j].coY == headZombieCol)
                {
                    for (int k = 0; k < vectorRowZombies[i].size(); k++)
                        if (vectorRowZombies[i][k].coY == headZombieCol)
                            vectorRowZombies[i][k].hp -= plantDps[SQUASH];
                    vectorRowPlants[i][j].hp -= 114514;
                }
                break;
            case PEPPER:
                for (int k = 0; k < vectorRowZombies[i].size(); k++)
                    vectorRowZombies[i][k].hp -= plantDps[PEPPER];
                vectorRowPlants[i][j].hp -= 114514;
                break;
            default:
                break;
            }
        }
        //植物对僵尸攻击
        if (headZombieCol == headPlantCol)
            for (int j = 0; j < vectorRowZombies[i].size(); j++)
            {
                if (vectorRowZombies[i][j].coY == headZombieCol)
                    vectorRowPlants[i][headPlantNum].hp -= zombieDps[vectorRowZombies[i][j].num];
            }
        //僵尸对植物攻击
        //攻击操作
        if (vectorRowPlants[i][headPlantNum].hp < 0)
        {
            for (int k = 0; k < vectorPlants.size(); k++)
            {
                if (vectorPlants[k].coX == i && vectorPlants[k].coY == headPlantCol)
                {
                    int num = vectorPlants[k].num;
                    newGame.moon += plantCost[num] / 5 + int(sqrt(plantHp[num]));
                    newGame.vectorPlants.erase(newGame.vectorPlants.begin() + k);
                    break;
                }
            }
            newGame.plants[i][headPlantCol] = 0;
        }
        for (int j = 0;j<vectorRowZombies[i].size();i++){
            if(vectorRowZombies[i][j].hp<=0){
                //从z和vecZ中清除
                int x=vectorRowZombies[i][j].coX,y=vectorRowZombies[i][j].coY;
                int k=0;
                while(zombies[i][j][k]!=-1){
                    if(zombies[i][j][k]==vectorRowZombies[i][j].num)
                        zombies[i][j][k]=0;
                    k++;
                }
                for(int l=0;l<vectorZombies.size();l++){
                    if(vectorZombies[l].coX==x&&vectorZombies[l].coY==y&&vectorZombies[l].num==vectorRowZombies[i][j].num&&vectorZombies[l].index==vectorRowZombies[i][j].index){
                        vectorZombies.erase(vectorZombies.begin()+l);
                        break;
                    }
                }
            }
        }
        //清理战场
    }
    // newGame.maintain(player);  ?
    //对操作进行运算
    return newGame;
}
extern "C" _declspec(dllexport) void player_ai(IPlayer *player)
{
    int Type = player->Camp->getCurrentType();
    static Game game;
    game.maintain(player);
    if (Type == 0) //铲除植物请使用game.plantremove()
    {
        /*int player->getNotBrokenLines();
        int player->getKillZombiesScore();
        int player->getLeftPlants();
        int player->getScore();
        int player->getTime();
        int player->Camp->getRows();
        int player->Camp->getColumns();
        int player->Camp->getPlantCD();
        int** player->Camp->getCurrentPlants();
        int*** player->Camp->getCurrentZombies();
        int* player->Camp->getLeftLines();
        int player->Camp->getSun();*/
    } //植物方
    if (Type == 1)
    {
        /*int player->getBrokenLinesScore();
        int player->getKillPlantsScore();
        int player->getScore();
        int player->getTime();
        int player->Camp->getRows();
        int player->Camp->getColumns();
        int* player->Camp->getPlantCD();
        int** player->Camp->getCurrentPlants();
        int*** player->Camp->getCurrentZombies();
        int* player->Camp->getLeftLines();
        int player->Camp->getSun();
        int calculate_zombie_nums(Zombies, 4, 9);*/
    } //僵尸方
}
