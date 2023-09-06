#include "ai.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
#define ZOMBIE_KIND 5
#define PLANT_KIND 6
#define TOTAL_TIME 2000
#define COLUMN 10
#define ROW 5
// FILE *file;
// errno_t err = fopen_s(&file, "D:\\2022 spring_semester\\pvz\\fc19_userpackage-master\\FC19_UI\\data.txt", "w+");
enum PlantType
{
    NOPLANT = 0,
    SUNFLOWER,
    SNOWPEA,
    PEASHOOTER,
    SMALLNUT,
    PEPPER,
    SQUASH
};

//僵 尸 种 类 4
enum ZombieType
{
    NOZOMBIE = 0,
    NORMAL,
    BUCKET,
    POLEVAULT,
    SLED,
    GARGANTUAR
};

// zrf 's code starts
const int plantCost[7] = {0, 50, 400, 100, 50, 125, 50};
const int plantCd[7] = {0, 10, 30, 10, 40, 60, 60};
const int zombieCost[6] = {0, 50, 125, 125, 300, 300};
const int zombieCd[6] = {0, 15, 20, 20, 25, 25};
const int plantHp[7] = {0, 300, 300, 300, 4000, 0, 0};
const int plantDps[7] = {0, 0, 20, 10, 0, 0, 0};
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
    int plantCD[7], zombieCD[6];     //记录双方在当前tick下冷却
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
                    plantCD[num] = plantCd[num];
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
                zombieCD[i] = zombieCd[i];
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
            if (plantCD[i] > 0)
                plantCD[i]--;
            if (plantCD[i] == 0)
                flagPlant[i] = 1;
        }

        for (int i = 0; i < 6; i++)
        {
            if (zombieCD[i] > 0)
                zombieCD[i]--;
            if (zombieCD[i] == 0)
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
            plantCD[i] = 0, flagPlant[i] = 1;
        for (int i = 0; i < 6; i++)
            zombieCD[i] = 0, flagZombie[i] = 1;
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
            newGame.plantCD[i] = this->plantCD[i], newGame.flagPlant[i] = this->flagPlant[i];
        for (int i = 0; i < 6; i++)
            newGame.zombieCD[i] = this->zombieCD[i], newGame.flagZombie[i] = this->flagZombie[i];
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
                newGame.plantCD[num] = plantCd[num];
                newGame.flagPlant[num] = 0;
                newGame.dps[i] += plantDps[num];
                newGame.plants[i][j] = num;
            }
            if (q.zombiePlace[i] > 0)
            {
                int num = q.zombiePlace[i];
                newGame.moon -= zombieCost[num];
                newGame.zombieCD[num] = zombieCd[num];
                newGame.flagZombie[num] = 0;
            }
        }
    newGame.maintain(player);
    //对操作进行运算
    return newGame;
}
// void

class Zombies_num
{
public:
    int normal;
    int bucket;
    int polevault;
    int sled;
    int gargantuar;
    int total_num;

    Zombies_num()
    {
        this->normal = this->bucket = this->polevault = this->sled = this->gargantuar = this->total_num = 0;
    }
    void compute_num(int ***zombies, int rows, int columns)
    {
        int num = 0;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                int k = 0;
                while (zombies[i][j][k] != -1)
                {
                    switch (zombies[i][j][k])
                    {
                    case NORMAL:
                        this->normal++;
                        break;
                    case BUCKET:
                        this->bucket++;
                        break;
                    case POLEVAULT:
                        this->polevault++;
                        break;
                    case SLED:
                        this->sled++;
                        break;
                    case GARGANTUAR:
                        this->gargantuar++;
                        break;
                    }
                    num++;
                    k++;
                }
            }
        }
    }
};
class Plants_num
{
public:
    int sunflower;
    int winterpeashooter;
    int peashooter;
    int smallnut;
    int pepper;
    int squash;

    Plants_num()
    {
        this->sunflower = this->winterpeashooter = this->peashooter = this->smallnut = this->pepper = this->squash = 0;
    }
    void compute_num(int **plants, int rows, int columns)
    {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
            {
                switch (plants[i][j])
                {
                case SUNFLOWER:
                    this->sunflower++;
                    break;
                case SNOWPEA:
                    this->winterpeashooter++;
                    break;
                case PEASHOOTER:
                    this->peashooter++;
                    break;
                case SMALLNUT:
                    this->smallnut++;
                    break;
                case PEPPER:
                    this->pepper++;
                    break;
                case SQUASH:
                    this->squash++;
                    break;
                }
            }
    }
};

int calculate_zombie_nums(int ***zombies, int rows, int columns)
{
    int num = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            int k = 0;
            while (zombies[i][j][k] != -1)
            {
                num++;
                k++;
            }
        }
    }
    return num;
}
int choose_Lines_not_Broken(int *Left_lines, int **plants, int column)
{
    for (int i = 0;; i++)
    {
        if (Left_lines[i] == 1 && plants[i][column] == NOPLANT)
            return i;
    }
    return rand() % ROW;
}
typedef struct pos_and_value
{
    int pos[2];
    double value;
} pos_and_value;

class value_plant_func
{
public:
    double noplant;
    pos_and_value sunflower;
    pos_and_value peashooter;
    pos_and_value winterpeashooter;
    pos_and_value smallnut;
    pos_and_value pepper;
    pos_and_value squash;
    int generating_row;
    IPlayer *player;
    Game game;
    // double value[PLANT_KIND + 1];
    // int choice[PLANT_KIND + 1] = {this->noplant, this->sunflower, this->peashooter, this->winterpeashooter, this->smallnut, this->pepper, this->squash};

    int NotBrokenLinesNum;
    int KillZombiesScore;
    int LeftPlants;
    int Score;
    int time;
    int *PlaceCD;
    int **Plants;
    int ***Zombies;
    int *LeftLines;
    int Sun;
    int zombie_nums;

    value_plant_func(int NotBrokenLinesNum,
                     int KillZombiesScore,
                     int Score,
                     int time,
                     int *PlaceCD,
                     int **Plants,
                     int ***Zombies,
                     int *LeftLines,
                     int Sun, IPlayer *player,
                     Game game)
    {
        this->NotBrokenLinesNum = NotBrokenLinesNum;
        this->KillZombiesScore = KillZombiesScore;
        this->Score = Score;
        this->time = time;
        this->PlaceCD = PlaceCD;
        this->Plants = Plants;
        this->Zombies = Zombies;
        this->LeftLines = LeftLines;
        this->Sun = Sun;
        this->player = player;
        this->generating_row = 1;
        this->game = game;
    }
    int **sum_plants_per_row()
    { // [rows,plants_kind] = num_per_row
        int **plants_num_format = (int **)malloc(ROW * sizeof(int *));
        for (int i = 0; i < ROW; i++)
        {
            plants_num_format[i] = (int *)malloc(sizeof(int) * PLANT_KIND);
            memset(plants_num_format[i], 0, PLANT_KIND * sizeof(int));
        }
        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COLUMN; j++)
            {
                switch (this->Plants[i][j])
                {
                case SUNFLOWER:
                    plants_num_format[i][SUNFLOWER]++;
                    break;
                case SNOWPEA:
                    plants_num_format[i][SNOWPEA]++;
                    break;
                case PEASHOOTER:
                    plants_num_format[i][PEASHOOTER]++;
                    break;
                case SMALLNUT:
                    plants_num_format[i][SMALLNUT]++;
                    break;
                case PEPPER:
                    plants_num_format[i][PEPPER]++;
                    break;
                case SQUASH:
                    plants_num_format[i][SQUASH]++;
                    break;
                }
            }
        }
        return plants_num_format;
    }
    void beginning_operation()
    {
        if (this->time <= 2)
        {
            this->player->PlacePlant(SUNFLOWER, this->generating_row, 1);
            this->player->PlacePlant(SMALLNUT, this->generating_row, COLUMN - 1);
        }
    }
    void GameState_2_50()
    {
        if (this->time > 2 && this->time < 200)
        {
            int alarming_flag = -1;
            for (int i = 0; i < ROW; i++)
            {
                if (i != this->generating_row)
                {
                    for (int j = 0; j < COLUMN; j++)
                    {
                        int k = 0;
                        while (this->Zombies[i][j][k] != -1)
                        {
                            if (j < 3)
                                alarming_flag = i;
                            if (this->Sun >= 70)
                                switch (this->Zombies[i][j][k])
                                {
                                case POLEVAULT:
                                case SLED:
                                    this->player->PlacePlant(SQUASH, i, (j - 1 < 0 ? 0 : j - 1));
                                    break;
                                case BUCKET:
                                    if (this->PlaceCD[SQUASH] == 0)
                                        this->player->PlacePlant(SQUASH, i, (j - 1 < 0 ? 0 : j - 1));
                                    else if (j < 3)
                                        this->player->PlacePlant(PEPPER, i, (j - 1 < 0 ? 0 : j - 1));
                                    break;
                                case GARGANTUAR:
                                    this->player->PlacePlant(SQUASH, i, (j - 1 < 0 ? 0 : j - 1));
                                    if (j < 4)
                                        this->player->PlacePlant(PEPPER, i, 8);
                                    break;
                                case NORMAL:
                                    this->player->PlacePlant(PEASHOOTER, i, 1);
                                    this->player->PlacePlant(SMALLNUT, i, (j - 1 < 0 ? 0 : j - 1));
                                    break;
                                }
                            k++;
                        }
                    }
                }
                else
                    for (int j = 0; j < COLUMN; j++)
                    {
                        int k = 0;
                        while (this->Zombies[this->generating_row][j][k] != -1)
                        {
                            if (this->Sun >= 70)
                                switch (this->Zombies[this->generating_row][j][k])
                                {

                                case POLEVAULT:
                                case BUCKET:
                                case SLED:
                                    this->player->PlacePlant(SQUASH, this->generating_row, 5);
                                    break;
                                case GARGANTUAR:
                                    this->player->PlacePlant(SQUASH, this->generating_row, (j - 1 < 0 ? 0 : j - 1));
                                    if (j < 4)
                                        this->player->PlacePlant(PEPPER, this->generating_row, 8);
                                    break;
                                case NORMAL:
                                    this->player->PlacePlant(SMALLNUT, this->generating_row, (j - 1 < 0 ? 1 : j - 1));

                                    break;
                                }
                            if (j < (this->sum_plants_per_row())[this->generating_row][SUNFLOWER] + 1 + 1 && this->PlaceCD[SQUASH] != 0)
                            {
                                this->player->PlacePlant(PEPPER, i, 8);
                            }
                            k++;
                        }
                    }
            }

            this->player->PlacePlant(SUNFLOWER, this->generating_row, (this->sum_plants_per_row())[this->generating_row][SUNFLOWER] + 1);
            if (alarming_flag != -1)
            {
                if (this->PlaceCD[SQUASH] == 0)
                {
                    this->player->PlacePlant(SQUASH, alarming_flag, COLUMN - 1);
                }
                else
                    this->player->PlacePlant(PEPPER, alarming_flag, COLUMN - 1);
            }
        }
    }

    void GameState_50_200()
    {
        if (this->time > 50 && this->time < 200)
        {
            if (this->Sun >= 400)
                this->player->PlacePlant(SNOWPEA, this->generating_row, 0);
        }
    }
    void value_peashooter_origin()
    {
        if (this->time > 50)
            if (this->PlaceCD[PEASHOOTER] == 0)
            {
                double **loss = (double **)malloc(ROW * sizeof(double *));
                for (int i = 0; i < ROW; i++)
                {
                    loss[i] = (double *)malloc(COLUMN * sizeof(double));
                    memset(loss[i], 0, COLUMN * sizeof(double));
                }
                double max = -10000, max_index[2] = {0, 0};
                for (int i = 0; i < ROW; i++)
                    for (int j = 0; j < COLUMN; j++)
                    {
                        if (this->Plants[i][j] != NOPLANT)
                            loss[i][j] = -10000;
                        else
                        {
                            //对行的参数
                            double row = (i == this->generating_row ? -10 : 0);
                            loss[i][j] += row;

                            //对列的参数
                            double column = (25);
                            loss[i][j] += column * exp(-column) - 10;

                            //对僵尸参数
                            double zombie[ZOMBIE_KIND] = {6, -10, -2, -40, -20};
                            for (int column0 = 0; j < COLUMN; j++)
                            {
                                int k = 0;
                                while (Zombies[i][column0][k] != -1)
                                {
                                    loss[i][j] += zombie[Zombies[i][column0][k] - 1] / (+COLUMN - j);
                                    k++;
                                }
                            }

                            //对植物参数
                            double plant[PLANT_KIND] = {2, 0, -2, 5, 2, 0};
                            for (int column0 = 0; j < COLUMN; j++)
                            {
                                if (this->Plants[i][column0] != NOPLANT)
                                    loss[i][j] += plant[this->Plants[i][column0]] * (1 + (column0 - COLUMN / 2) / 40);
                            }

                            //对时间的参数
                            double time_rate = 30;
                            loss[i][j] += time_rate * (1 / (1 + exp((+this->time - TOTAL_TIME / 5) / 200)) - 0.5);
                        }
                        if (max < loss[i][j])
                        {
                            max_index[0] = i;
                            max_index[1] = j;
                        }
                    }
                this->peashooter.pos[0] = max_index[0];
                this->peashooter.pos[1] = max_index[1];
                this->peashooter.value = max;
            }
    }
    bool exist_this_type_zombies(int *zombie, int type)
    {
        int k = 0;
        while (zombie[k] != -1)
        {
            if (zombie[k] == type)
                return true;
            k++;
        }
        return false;
    }
    int search_for_nearest_zombie(int ***zombie, int row, int column)
    {
        int nearest = 0;
        for (int j = 0; j < COLUMN; j++)
        {
            int k = 0;
            while (Zombies[row][j][k] != -1)
            {
                if (nearest > j - column)
                    nearest = j - column;
                k++;
            }
        }
        return nearest;
    }
    void judge_Lines_not_broken(double *final_choice)
    {
        for (int i = 0; i < ROW; i++)
        {
            if (LeftLines[i] == 0)
            {
                final_choice[i] = -10000;
            }
        }
    }
    void value_peashooter()
    {
        if (this->time > 30)
        {
            if (this->PlaceCD[PEASHOOTER] == 0)
            {
                for (int i = 0; i < ROW; i++)
                {
                    if (LeftLines[i] == 0)
                    {
                        for (int j = 0; j < COLUMN; j++)
                        {
                            int k = 0;
                            while (Zombies[i][j][k] != -1)
                            {
                                k++;
                            }
                            if (k == 1 && Zombies[i][j][0] == NORMAL && j >= COLUMN - 2)
                            {
                                this->player->PlacePlant(PEASHOOTER, i, 0);
                            }
                            else if (k > 0 && (exist_this_type_zombies(Zombies[i][j], POLEVAULT) || exist_this_type_zombies(Zombies[i][j], BUCKET)) && Sun < 400 && time < 500 && j < 4)
                            {
                                int start = 0;
                                while (Plants[i][start] != NOPLANT)
                                {
                                    start++;
                                }
                                if (search_for_nearest_zombie(Zombies, i, start) >= 1)
                                {
                                    player->PlacePlant(PEASHOOTER, i, start);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    int *rank(double *array, int len)
    {
        double max = array[0];
        int *serial_num = (int *)malloc(len * sizeof(int));
        for (int i = 0; i < len; i++)
        {
            serial_num[i] = i;
        }
        for (int i = 0; i < len - 1; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (array[j] < array[j + 1])
                {
                    double swap = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = swap;
                    int serial_swap = serial_num[j];
                    serial_num[j] = serial_num[j + 1];
                    serial_num[j + 1] = serial_swap;
                }
            }
        }
        return serial_num;
    }
    void value_sunflower()
    {
        if (this->time > 10)
            if (this->PlaceCD[SUNFLOWER] == 0)
            {
                double score[5] = {0, 0, 0, 0, 0};
                judge_Lines_not_broken(score);
                for (int i = 0; i < ROW; i++)
                {
                    for (int j = 0; j < COLUMN; j++)
                    {
                        if (Plants[i][j] == SUNFLOWER)
                            score[i] -= 10;
                        if (Plants[i][j] == PEASHOOTER)
                            score[i] += 50 * (1 * (exp(-j)));
                        if (Plants[i][j] == SNOWPEA)
                            score[i] += 100 * (1 * (exp(-j)));
                        if (Plants[i][j] == SMALLNUT)
                            score[i] += 100 * (-0.01 * (j - 5) * (j - 5) + 1);
                    }
                }
                for (int i = 0; i < ROW; i++)
                    for (int j = 0; j < COLUMN; j++)
                    {
                        int k = 0;
                        while (Zombies[i][j][k] != -1)
                        {
                            if (Zombies[i][j][k] == NORMAL)
                                score[i] -= 10 * (1 / (0.1 + j));
                            if (Zombies[i][j][k] == BUCKET)
                                score[i] -= 50 * (1 / (0.1 + j));
                            if (Zombies[i][j][k] == POLEVAULT)
                                score[i] -= 30 * (1 / (0.1 + j));
                            if (Zombies[i][j][k] == GARGANTUAR)
                                score[i] -= 100 * (1 / (0.1 + j));
                            if (Zombies[i][j][k] == SLED)
                                score[i] -= 80 * (1 / (0.1 + j));
                            k++;
                        }
                    }

                int sunflower_num_in_generating_row = 0;
                for (int j = 0; j < COLUMN; j++)
                {
                    if (Plants[this->generating_row][j] == SUNFLOWER)
                        sunflower_num_in_generating_row++;
                }
                score[this->generating_row] += 100 * (1 / (sunflower_num_in_generating_row + 1));

                int *serial_num = rank(score, ROW);
                for (int i = 0; i < ROW; i++)
                {
                    int j = 0;
                    while (Plants[serial_num[0]][j] == NOPLANT)
                    {
                        j++;
                    }
                    player->PlacePlant(SUNFLOWER, serial_num[0], j);
                }
            }
    }
    void value_smallmnut()
    {
        if (this->PlaceCD[SMALLNUT] == 0)
            if (this->time > 20)
            {
                double score[ROW] = {0, 0, 0, 0, 0};
                judge_Lines_not_broken(score);

                // value plants
                double plants_score[7] = {0, 5, 20, 20, -7, -1, 0};
                for (int i = 0; i < ROW; i++)
                {
                    for (int j = 0; j < COLUMN; j++)
                    {
                        double distance_cost = 1;
                        switch (Plants[i][j])
                        {
                        case SUNFLOWER:
                            distance_cost = 1.5 - 0.05 * j;
                            break;
                        case PEASHOOTER:
                            distance_cost = 2 - 0.09 * j;
                            break;
                        case SNOWPEA:
                            distance_cost = 2 - 0.1 * j;
                            break;
                        }
                        score[i] += Plants[i][j] * plants_score[i] * distance_cost;
                    }
                }

                // value zombies;
                double zombie_cost[5] = {2.0, 10, 12, -4, -6};
                int nearest_zombie_per_row[5] = {0, 0, 0, 0, 0};
                for (int i = 0; i < ROW; i++)
                {
                    for (int j = COLUMN - 1; j >= 0; j--)
                    {
                        int k = 0;
                        while (Zombies[i][j][k] != -1)
                        {
                            double distance_cost = 1;
                            switch (Zombies[i][j][k])
                            {
                            case NORMAL:
                                distance_cost = 1.2 - 0.02 * (j);
                                break;
                            case POLEVAULT:
                                distance_cost = 1.1 - 0.01 * j;
                                break;
                            case BUCKET:
                                distance_cost = 1.3 - 0.04 * j;
                                break;
                            }
                            score[i] += zombie_cost[(Zombies[i][j][k] - 1)] * distance_cost;
                            k++;
                            nearest_zombie_per_row[i] = j;
                        }
                    }
                }

                int *serial_num = rank(score, ROW);
                for (int i = 0; i < ROW; i++)
                {
                    int j = 0;

                    while (Plants[serial_num[0]][j] == NOPLANT)
                    {
                        j++;
                    }
                    player->PlacePlant(SUNFLOWER, serial_num[0], nearest_zombie_per_row[serial_num[i]] - 1);
                }
            }
    }
    void value()
    {
        this->value_peashooter();
        this->value_sunflower();
        this->value_smallmnut();
        // double max = -100000;
        // double value[7] = {this->noplant, this->sunflower.value, this->winterpeashooter.value, this->peashooter.value, this->smallnut.value, this->squash.value, this->pepper.value};
        // this->player->PlacePlant(PEASHOOTER, this->peashooter.pos[0], this->peashooter.pos[1]);
    }
    void make_decision()
    {
        this->beginning_operation();
        this->GameState_2_50();
        this->GameState_50_200();
        this->value();
    }
};
class value_zombie_func //  应加入多次进攻未果 换线的操作
{
public:
    int noZombie;
    int normal_choice;
    int bucket_choice;
    int polevault_choice;
    int sled_choice;
    int gargantuar_choice;
    double value[ZOMBIE_KIND];
    int choice[ZOMBIE_KIND] = {this->normal_choice, this->bucket_choice, this->polevault_choice, this->sled_choice, this->gargantuar_choice}; // KIND->ROW

    int BrokenLinesScore;
    int KillPlantsScore;
    int LeftPlants;
    int Score;
    int time;
    int *PlaceCD;
    int **Plants;
    int ***Zombies;
    int *LeftLines;
    int Sun;
    int zombie_nums;
    Game game;

    value_zombie_func(int BrokenLinesScore,
                      int KillPlantsScore,
                      int Score,
                      int time,
                      int *PlaceCD,
                      int **Plants,
                      int ***Zombies,
                      int *LeftLines,
                      int Sun,
                      int zombie_nums,
                      Game game)
    {
        this->normal_choice = this->bucket_choice = this->polevault_choice = this->sled_choice = this->gargantuar_choice = 0;
        this->BrokenLinesScore = BrokenLinesScore;
        this->KillPlantsScore = KillPlantsScore;
        this->Score = Score;
        this->time = time;
        this->PlaceCD = PlaceCD;
        this->Plants = Plants;
        this->Zombies = Zombies;
        this->LeftLines = LeftLines;
        this->Sun = Sun;
        this->zombie_nums = zombie_nums;
        this->game = game;
        for (int i = 0; i < ZOMBIE_KIND; i++)
            this->value[i] = 0;
        memset(this->choice, 0, ZOMBIE_KIND * (sizeof(int)));
    }
    // void input_data()
    // {
    //     for (int i = 0; i < ROW; i++)
    //     {
    //         fputc(this->choice[i], file);
    //         fprintf(file, " %.6f ", this->value[i]);
    //     }
    //     fprintf(file, "\n");
    // }
    int whether_too_costy(int *cost)
    {
        double average = 0, square_distance = 0;
        for (int i = 0; i < ROW; i++)
        {
            average += cost[i];
        }
        average /= 5;
        for (int i = 0; i < ROW; i++)
        {
            square_distance += (cost[i] - average) * (cost[i] - average);
        }
        square_distance = pow(square_distance, 0.5);
        square_distance /= 5;

        if (square_distance > pow(this->time, 0.01) * 100)
        {
            return 1;
        }
        else
            return 0;
    }
    void make_decision(int *decision) //[ KIND , ROW ]
    {
        int *cost = this->game.zombieCostPerRow;
        if (whether_too_costy(cost) == 0)
        {
            double max = value[0];

            for (int i = 0; i < 5; i++)
            {
                if (max < this->value[i])
                {
                    max = this->value[i];
                    decision[0] = i + 1;
                    decision[1] = this->choice[i];
                }
            }
        }
        else
        {
            double min = value[0];

            for (int i = 0; i < 5; i++)
            {
                if (min > this->value[i])
                {
                    min = this->value[i];
                    decision[0] = i + 1;
                    decision[1] = this->choice[i];
                }
            }
            if (this->zombie_nums > (this->time / 100 + 4))
            {
                decision[0] = decision[1] = NOZOMBIE;
            }
        }
    }
    // void value_nozombie()
    // {
    //     int final_choice[ROW] = {0, 0, 0, 0, 0};
    //     /*
    //             this->NotBrokenLinesNum = NotBrokenLinesNum;
    //             this->KillZombiesScore = KillZombiesScore;
    //             this->LeftPlants = LeftPlants;
    //             this->Score = Score;
    //             this->time = time;
    //             this->PlaceCD = PlaceCD;
    //             this->Plants = Plants;
    //             this->Zombies = Zombies;
    //             this->LeftLines = LeftLines;
    //             this->Sun = Sun;
    //     */
    //     for (int i = 0; i < ROW; i++)
    //     {
    //         final_choice[i] += 0;
    //     }
    // }
    bool whether_need_compute(int kind)
    { //需要为0 不需要为1
        if (this->PlaceCD[kind - 1] > 0)
        {
            this->choice[kind - 1] = 0;
            this->value[kind - 1] = -100000;
            return true;
        }
        else
            return false;
    }
    double zombie_cost(int row, double *zombies_paras, double distance_cost, double distance_rate, int kind)
    {
        double cost = 0.0;
        if (this->LeftLines[row] == 0)
        {
            cost = -100000;
        }
        else
        {
            int num_per_row = 0;
            double too_many_zombies_cost = -1.5;
            for (int j = 0; j < COLUMN; j++)
            {
                int k = 0;
                while (this->Zombies[row][j][k] != -1)
                {
                    switch (kind)
                    {
                    case POLEVAULT:
                        cost += zombies_paras[this->Zombies[row][j][k] - 1] * ((COLUMN - j - distance_cost) * (COLUMN - j - distance_cost));
                        break;
                    default:
                        cost += zombies_paras[this->Zombies[row][j][k] - 1] * (-distance_rate * (COLUMN - j - distance_cost) * (COLUMN - j - distance_cost) + 2);
                    }
                    k++;
                    num_per_row++;
                }
            }
            cost += num_per_row * too_many_zombies_cost;
        }
        return cost;
    }
    int **sum_plants_per_row()
    { // [rows,plants_kind] = num_per_row
        int **plants_num_format = (int **)malloc(ROW * sizeof(int *));
        for (int i = 0; i < ROW; i++)
        {
            plants_num_format[i] = (int *)malloc(sizeof(int) * PLANT_KIND);
            memset(plants_num_format[i], 0, PLANT_KIND * sizeof(int));
        }
        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COLUMN; j++)
            {
                switch (this->Plants[i][j])
                {
                case SUNFLOWER:
                    plants_num_format[i][SUNFLOWER - 1]++;
                    break;
                case SNOWPEA:
                    plants_num_format[i][SNOWPEA - 1]++;
                    break;
                case PEASHOOTER:
                    plants_num_format[i][PEASHOOTER - 1]++;
                    break;
                case SMALLNUT:
                    plants_num_format[i][SMALLNUT - 1]++;
                    break;
                case PEPPER:
                    plants_num_format[i][PEPPER - 1]++;
                    break;
                case SQUASH:
                    plants_num_format[i][SQUASH - 1]++;
                    break;
                }
            }
        }
        return plants_num_format;
    }
    double plant_cost(int row, int **plants_num_format, double *plants_para, int kind)
    {
        double cost = 0.0;
        switch (kind)
        {
        case NORMAL:
            if (plants_num_format[row][SMALLNUT - 1] > 0 && plants_num_format[row][PEASHOOTER - 1] + plants_num_format[row][SNOWPEA - 1] > 0)
                plants_para[SMALLNUT - 1] *= (plants_num_format[row][PEASHOOTER - 1] * 1 + plants_num_format[row][SNOWPEA - 1] * 2);
            break;
        case BUCKET:
            if (plants_num_format[row][SMALLNUT - 1] > 0 && plants_num_format[row][SNOWPEA - 1] > 0)
                plants_para[SMALLNUT - 1] *= (plants_num_format[row][PEASHOOTER - 1] * 0.2 + plants_num_format[row][SNOWPEA - 1]);
            break;
        case POLEVAULT:
            if (plants_num_format[row][SMALLNUT - 1] > 0 && plants_num_format[row][PEASHOOTER - 1] + plants_num_format[row][SNOWPEA - 1] > 0)
            {
                plants_para[SMALLNUT - 1] *= ((1.5 - plants_num_format[row][SMALLNUT - 1]) * (3 - plants_num_format[row][PEASHOOTER - 1] + plants_num_format[row][SNOWPEA - 1]));
            }
        case SLED:
            if (plants_num_format[row][SMALLNUT - 1] > 1 && plants_num_format[row][PEASHOOTER - 1] + plants_num_format[row][SNOWPEA - 1] > 0)
            {
                plants_para[SMALLNUT - 1] *= (plants_num_format[row][SMALLNUT - 1] * plants_num_format[row][SMALLNUT - 1]) * (plants_num_format[row][SNOWPEA - 1]);
            }
            break;
        case GARGANTUAR:
            if (plants_num_format[row][SNOWPEA - 1] > 1)
            {
                plants_para[SNOWPEA - 1] *= (plants_num_format[row][SNOWPEA - 1] + 1);
            }
        }
        plants_para[SUNFLOWER - 1] *= (1 + 1 / (COLUMN - plants_num_format[row][SUNFLOWER - 1] + 1));
        for (int j = 0; j < COLUMN; j++)
        {
            if (Plants[row][j] != NOPLANT)
                cost += plants_para[Plants[row][j] - 1] * (plants_para[Plants[row][j] - 1] > 0 ? (j + 1) * (j + 1) : (COLUMN - j));
        }
        return cost;
    }
    int max_index(double *a, int length)
    {
        double max = -10000;
        int index = 0;
        for (int i = 0; i < length; i++)
        {
            if (max < a[i])
            {
                max = a[i];
                index = i;
            }
        }
        return index;
    }
    /*
            NORMAL,
            BUCKET,
            POLEVAULT,
            SLED,
            GARGANTUAR
    */

    /*
        SUNFLOWER,
        SNOWPEA,
        PEASHOOTER,
        SMALLNUT,
        PEPPER,
        SQUASH
    */
    void judge_Lines_not_broken(double *final_choice)
    {
        for (int i = 0; i < ROW; i++)
        {
            if (LeftLines[i] == 0)
            {
                final_choice[i] = -10000;
            }
        }
    }
    void value_normal()
    {
        double final_choice[ROW] = {0, 0, 0, 0, 0};
        judge_Lines_not_broken(final_choice);
        if (this->whether_need_compute(NORMAL))
        {
            return;
        }

        //遍历zombie
        double zombies_paras[ZOMBIE_KIND] = {-5, 4, 2, 3, 1};
        double distance_cost = 1, distance_rate = 0.05;
        for (int i = 0; i < ROW; i++)
        {
            final_choice[i] += this->zombie_cost(i, zombies_paras, distance_cost, distance_rate, NORMAL);
        }

        //遍历plant
        int plants_num_format[ROW][PLANT_KIND] = {{0}};
        double plants_para[PLANT_KIND] = {8.332, -8.105, -2.6, -1.945, -98.76, 5.166};
        int **sum_plants_per_row0 = this->sum_plants_per_row();
        for (int i = 0; i < ROW; i++)
        {
            final_choice[i] += this->plant_cost(i, sum_plants_per_row0, plants_para, NORMAL);
        }

        //考虑time
        double time_cost = 20 * (1 / (1 + exp((this->time - TOTAL_TIME / 2) / 100)) - 0.5);
        for (int i = 0; i < ROW; i++)
            final_choice[i] += time_cost;

        //考虑Sun
        double sun_baseline = 60, sun_sub = 0.2;
        double sun_cost = (this->Sun - sun_baseline > 0 ? 1 / (1 + exp((-this->Sun + sun_baseline) / 100)) * 15 : -pow(sun_baseline - this->Sun, 1 / sun_sub));
        for (int i = 0; i < ROW; i++)
            final_choice[i] += sun_cost;

        this->choice[NORMAL - 1] = this->max_index(final_choice, ROW);
        this->value[NORMAL - 1] = final_choice[this->choice[NORMAL - 1]];
    }

    void value_bucket()
    {
        double final_choice[ROW] = {0, 0, 0, 0, 0};
        judge_Lines_not_broken(final_choice);
        if (this->whether_need_compute(BUCKET))
        {
            return;
        }

        //遍历zombie
        double zombies_paras[ZOMBIE_KIND] = {2.5, -4, this->time < 100 ? -100 : -5, 2, -2};
        double distance_cost = 2.5, distance_rate = 0.1;
        for (int i = 0; i < ROW; i++)
        {
            final_choice[i] += this->zombie_cost(i, zombies_paras, distance_cost, distance_rate, BUCKET);
        }

        //遍历plant
        int plants_num_format[ROW][PLANT_KIND] = {{0}};
        double plants_para[PLANT_KIND] = {6.26, 3.14, 2.22, 3.01, -100.64, -4.855};
        int **sum_plants_per_row = this->sum_plants_per_row();
        for (int i = 0; i < ROW; i++)
        {
            final_choice[i] += this->plant_cost(i, sum_plants_per_row, plants_para, BUCKET);
        }

        //考虑time
        double time_cost = 20 * (1 / (1 + exp((-this->time + TOTAL_TIME / 3) / 100)) - 0.5);
        for (int i = 0; i < ROW; i++)
            final_choice[i] += time_cost;

        //考虑Sun
        double sun_baseline = 150, sun_sub = 0.5;
        double sun_cost = (this->Sun - sun_baseline > 0 ? 1 / (1 + exp(-this->Sun + sun_baseline)) * 5 : -pow(sun_baseline - this->Sun, 1 / sun_sub));
        for (int i = 0; i < ROW; i++)
            final_choice[i] += sun_cost;

        this->choice[BUCKET - 1] = this->max_index(final_choice, ROW);
        this->value[BUCKET - 1] = final_choice[this->choice[BUCKET - 1]];
    }

    void value_polevault()
    {
        double final_choice[ROW] = {0, 0, 0, 0, 0};
        judge_Lines_not_broken(final_choice);
        if (this->whether_need_compute(POLEVAULT))
        {
            return;
        }

        //遍历zombie
        double zombies_paras[ZOMBIE_KIND] = {1, this->time < 100 ? -100 : -5, -1.5, 2, -3};
        double distance_cost = 2.5, distance_rate = 0.1;
        for (int i = 0; i < ROW; i++)
        {
            final_choice[i] += this->zombie_cost(i, zombies_paras, distance_cost, distance_rate, POLEVAULT);
        }

        //遍历plant
        int plants_num_format[ROW][PLANT_KIND] = {{0}};
        double plants_para[PLANT_KIND] = {5, -2, -1, 8, -100, -1}; //偏好建国
        int **sum_plants_per_row = this->sum_plants_per_row();
        for (int i = 0; i < ROW; i++)
        {
            final_choice[i] += this->plant_cost(i, sum_plants_per_row, plants_para, POLEVAULT);
        }

        //考虑time
        double time_cost = 20 * (1 / (1 + exp((-this->time + TOTAL_TIME / 5) / 100)) - 0.5);
        for (int i = 0; i < ROW; i++)
            final_choice[i] += time_cost;

        //考虑Sun
        double sun_baseline = 120, sun_sub = 0.4;
        double sun_cost = (this->Sun - sun_baseline > 0 ? 1 / (1 + exp(-this->Sun + sun_baseline)) * 6 : -pow(sun_baseline - this->Sun, 1 / sun_sub));
        for (int i = 0; i < ROW; i++)
            final_choice[i] += sun_cost;

        this->choice[POLEVAULT - 1] = this->max_index(final_choice, ROW);
        this->value[POLEVAULT - 1] = final_choice[this->choice[POLEVAULT - 1]];
    }

    void value_sled()
    {
        double final_choice[ROW] = {0, 0, 0, 0, 0};
        judge_Lines_not_broken(final_choice);
        if (this->whether_need_compute(SLED))
        {
            return;
        }

        //遍历zombie
        double zombies_paras[ZOMBIE_KIND] = {3, -2, -1, -7, -4};
        double distance_cost = 2.5, distance_rate = 0.1;
        for (int i = 0; i < ROW; i++)
        {
            final_choice[i] += this->zombie_cost(i, zombies_paras, distance_cost, distance_rate, SLED);
        }

        //遍历plant
        int plants_num_format[ROW][PLANT_KIND] = {{0}};
        double plants_para[PLANT_KIND] = {5, 10, 3, 6, -100, 1}; //偏好建国 and 冰豌豆
        int **sum_plants_per_row = this->sum_plants_per_row();
        for (int i = 0; i < ROW; i++)
        {
            final_choice[i] += this->plant_cost(i, sum_plants_per_row, plants_para, SLED);
        }

        //考虑time
        double time_cost = 20 * (1 / (1 + exp((-this->time + TOTAL_TIME / 5) / 200)) - 0.5);
        for (int i = 0; i < ROW; i++)
            final_choice[i] += time_cost;

        //考虑Sun
        double sun_baseline = 200, sun_sub = 0.5;
        double sun_cost = (this->Sun - sun_baseline > 0 ? 1 / (1 + exp(-this->Sun + sun_baseline + 100) / 200) * 10 : -pow(sun_baseline - this->Sun, 1 / sun_sub));
        for (int i = 0; i < ROW; i++)
            final_choice[i] += sun_cost;

        this->choice[SLED - 1] = this->max_index(final_choice, ROW);
        this->value[SLED - 1] = final_choice[this->choice[SLED - 1]];
    }
    void value_gargantuar()
    {
        double final_choice[ROW] = {0, 0, 0, 0, 0};
        judge_Lines_not_broken(final_choice);
        if (this->whether_need_compute(GARGANTUAR))
        {
            return;
        }

        //遍历zombie
        double zombies_paras[ZOMBIE_KIND] = {2, -4, -5, -20, -15};
        double distance_cost = 2.5, distance_rate = 0.1;
        for (int i = 0; i < ROW; i++)
        {
            final_choice[i] += this->zombie_cost(i, zombies_paras, distance_cost, distance_rate, GARGANTUAR);
        }

        //遍历plant
        int plants_num_format[ROW][PLANT_KIND] = {{0}};
        double plants_para[PLANT_KIND] = {0, 98.75, 2.63, 5.82, -101.2, -9.885}; //偏好建国 and 冰豌豆
        int **sum_plants_per_row = this->sum_plants_per_row();
        for (int i = 0; i < ROW; i++)
        {
            final_choice[i] += this->plant_cost(i, sum_plants_per_row, plants_para, GARGANTUAR);
        }

        //考虑time
        double time_cost;
        if (abs(this->time - 500) < 25 || abs(this->time - 1000) < 25 || abs(this->time - 1500) < 25)
            time_cost = 100;
        time_cost = 100 * (1 / (1 + exp((-this->time + TOTAL_TIME / 5) / 400)) - 0.4);
        for (int i = 0; i < ROW; i++)
            final_choice[i] += time_cost;

        //考虑Sun
        double sun_baseline = 350, sun_sub = 0.6;
        double sun_cost = 1 / (1 + exp(-this->Sun + sun_baseline + 100) / 200) * 10;
        for (int i = 0; i < ROW; i++)
            final_choice[i] += sun_cost;

        this->choice[GARGANTUAR - 1] = this->max_index(final_choice, ROW);
        this->value[GARGANTUAR - 1] = final_choice[this->choice[GARGANTUAR - 1]];
    }
};
extern "C" _declspec(dllexport) void player_ai(IPlayer *player)
{
    static Game game;
    game.maintain(player);
    /*
    class ICamp
    {
    public:
        virtual int** getCurrentPlants() = 0;

        获 取 现 在 场 上 存 活 的 植 物 情 况。
        Plants [ i ] [ j ] 即 为 第 i 行 j 列 的 植 物 情 况， 0代 表 不 存 在

        virtual int*** getCurrentZombies() = 0;

        Zombies [ i ] [ j ] 即 为 第 i 行 j 列 格 子 中 的 所 有 僵 尸，
        如 果 该 格 子 中 有k（k>=0） 个 僵 尸， 则Zombies [ i ] [ j ] 的 长 度 为k+1，
        最 后 一 位Zombies [ i ] [ j ] [ k ] 为−1， 代 表 这 一 格 结 束

        virtual int getSun() = 0;

        获 取 己 方 阵 营 当 前 所 剩 的 阳 光 （月 光） 数

        virtual int* getPlantCD() = 0;

        获 取 植 物 或 僵 尸 种 植 冷 却 时 间， 植 物 方 调 用 时 仅 返 回 植 物 的 种 植CD， 僵 尸 方 同 理。
        植 物 方 返 回 的 数 组 依 次 是 太 阳 花， 冰 豌 豆 射 手， 豌 豆 射 手， 坚 果 墙， 火 爆 辣 椒， 倭 瓜；
        僵 尸 方 返 回 的 数 组 依 次 是 普 通 僵 尸， 铁 桶 僵 尸， 撑 杆 跳 僵 尸， 雪 橇 车 僵 尸， 伽 刚 特 尔。 数 组 下 标 从0开 始

        virtual int* getLeftLines() = 0

        获 取 植 物 方 各 行 是 否 被 攻 破， 长 度 为 行 数， 1为 该 行 未 被 攻 破， 0为 被 攻 破

        virtual int getRows() = 0;获 取 场 地 的 行 数

        virtual int getColumns() = 0;获 取 场 地 的 列 数

        virtual int getCurrentType() = 0;
    };
    class IPlayer
    {
    public:
        ICamp* Camp;
        virtual void PlacePlant(int type, int x, int y) = 0;  横着数为x 竖着数为y

        //参 数： 放 置 的 行 数x , 列 数y， 植 物 的 种 类type , 从1~6依 次 为 太 阳 花， 冰 豌 豆 射 手， 豌 豆 射 手， 坚 果
        墙， 火 爆 辣 椒， 倭 瓜 3 //作 用： 植 物 方 调 用 种 植 植 物。 僵 尸 方 调 用 无 效。 注 意 一 个 回 合 内 一 种 植 物 只 能 种 植 一 次，
        一 个 回 合 种 植 多 株 相 同 植 物 只 取 第 一 次。  当 要 种 植 植 物 的 种 植 CD 不 为 0 或 者 阳 光 不 足 或 者 待 种 植 的 位 置 已 经 存 在 植 物 则 种 植 无 效。

        virtual void PlaceZombie(int type, int y) = 0;

        放 置 的 列 数y， 僵 尸 的 种 类type , 从1~5依 次 为 普 通 僵 尸， 铁 桶 僵 尸， 撑 杆 跳 僵 尸， 雪 橇 车 僵 尸， 伽 刚 特 尔。
        作 用： 僵 尸 方 调 用 放 置 僵 尸。 植 物 方 调 用 无 效。 注 意 一 个 回 合 内 一 种 僵 尸 只 能 放 置 一 次，
        一 个 回 合 放 置 多 只 相 同 僵 尸 只 取 第 一 次。 当 要 放 置 的 僵 尸 放 置CD不 为0或 者 阳 光 不 足 则 放 置 无 效。

        virtual int getTime() = 0; 获 取 当 前 回 合 数
        virtual int getScore() = 0;获 取 己 方 分 数
        virtual int getKillPlantsScore() = 0;获 取 己 方 作 为 僵 尸 方 时 通 过 杀 死 植 物 得 到 的 分 数
        virtual int getKillZombiesScore() = 0;获 取 己 方 作 为 植 物 方 时 通 过 杀 死 僵 尸 得 到 的 分 数
        virtual int getNotBrokenLines() = 0;  返 回 己 方 作 为 植 物 方 时 未 被 攻 破 的 行 数
        virtual int getBrokenLinesScore() = 0;   返 回 己 方 作 为 僵 尸 方 时 通 过 攻 破 一 整 行 获 得 的 分 数
        virtual int getLeftPlants() = 0;;获 取 己 方 作 为 植 物 方 时 结 束 时 剩 余 的 植 物 个 数
    };*/
    int Type = player->Camp->getCurrentType();
    //植 物 种 类 2

    if (Type == 0)
    { //植物方
        int NotBrokenLinesNum = player->getNotBrokenLines();
        int KillZombiesScore = player->getKillZombiesScore();
        int LeftPlants = player->getLeftPlants();
        int Score = player->getScore();
        int time0 = player->getTime();
        int rows = player->Camp->getRows();
        int columns = player->Camp->getColumns();
        int *PlaceCD = player->Camp->getPlantCD();
        int **Plants = player->Camp->getCurrentPlants();
        int ***Zombies = player->Camp->getCurrentZombies();
        int *LeftLines = player->Camp->getLeftLines();
        int Sun = player->Camp->getSun();
        // Zombies_num zombies_num;
        // zombies_num.compute_num(Zombies, rows, columns);
        // Plants_num plants_num;
        // plants_num.compute_num(Plants, rows, columns);
        // player->PlacePlant(SUNFLOWER, (choose_Lines_not_Broken(LeftLines, Plants, plants_num.sunflower / 5 + 1)) % 5, plants_num.sunflower / 5 + 1);
        // player->PlacePlant(SMALLNUT, (choose_Lines_not_Broken(LeftLines, Plants, plants_num.smallnut / 5 + 2)+3)%5, plants_num.smallnut / 5 + 2);
        // if (plants_num.sunflower < 3)
        //     player->PlacePlant(SUNFLOWER, 0, plants_num.sunflower + 1);
        // player->PlacePlant(SMALLNUT, 0, plants_num.smallnut + 5);
        // player->PlacePlant(SQUASH, 0, 4);
        // player->PlacePlant(SQUASH, (choose_Lines_not_Broken(LeftLines, Plants, plants_num.squash / 5 + 4) ) % 5, (plants_num.squash) / 5 + 4);
        // if (time0 > 6)
        //     player->PlacePlant(PEASHOOTER, (choose_Lines_not_Broken(LeftLines, Plants, (plants_num.peashooter) / 5)+1)%5, (plants_num.peashooter + 4) / 5);
        // if (Sun > 400)
        // player->PlacePlant(SNOWPEA, 0, 0);

        value_plant_func value(NotBrokenLinesNum, KillZombiesScore, Score, time0, PlaceCD, Plants, Zombies, LeftLines, Sun, player, game);
        value.make_decision();
    }
    if (Type == 1)
    {
        //僵尸方
        int BrokenLinesScore = player->getBrokenLinesScore();
        int KillPlantsScore = player->getKillPlantsScore();
        int Score = player->getScore();
        int time = player->getTime();
        int rows = player->Camp->getRows();
        int columns = player->Camp->getColumns();
        int *PlaceCD = player->Camp->getPlantCD();
        int **Plants = player->Camp->getCurrentPlants();
        int ***Zombies = player->Camp->getCurrentZombies();
        int *LeftLines = player->Camp->getLeftLines();
        int Sun = player->Camp->getSun();
        if (time > 3)
        {
            int zombie_num = calculate_zombie_nums(Zombies, 4, 9);
            value_zombie_func value(BrokenLinesScore, KillPlantsScore, Score, time, PlaceCD, Plants, Zombies, LeftLines, Sun, zombie_num, game);
            value.value_normal();
            value.value_bucket();
            value.value_polevault();
            value.value_sled();
            value.value_gargantuar();
            int decision[2] = {0, 0};
            value.make_decision(decision);

            // for (int i = 0; i < rows; i++)
            // {
            //     for (int j = 0; j < columns; j++)
            //     {
            //         int k = 0;
            //         while (Zombies[i][j][k] != -1)
            //         {
            //             // . . .
            //             k++;
            //         }
            //     }
            // }
            if (decision[0] != NOZOMBIE)
            {
                player->PlaceZombie((decision[0] > ZOMBIE_KIND ? NORMAL : decision[0]), decision[1] > ROW - 1 ? ROW - 1 : decision[1]);
            }
        }
        else
        {
            player->PlaceZombie(POLEVAULT, 1);
            player->PlaceZombie(NORMAL, 2);
            player->PlaceZombie(BUCKET, 3);
        }
    }
}
