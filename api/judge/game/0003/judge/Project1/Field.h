#ifndef FIELD_H
#define FIELD_H
#include "Camp.h"
#include "Plants.h"
#include "Zombies.h"
#include "cmath"
#include <stdio.h>
#include <string>
#include <typeinfo>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>

using namespace std;
#ifdef _DEBUG

#define new  new(_NORMAL_BLOCK, __FILE__, __LINE__)

#endif
const int ENDTIME = 2000; //结束时间
//格子类，认为一个格子可以同时存在植物和僵尸，此时僵尸开始攻击植物
class grid {
private:
    bool exists_plant;
    bool exists_zombie;
    plants* plant;
    vector<int> zombie;
public:
    //默认构造函数（游戏开始时调用），默认为空
    grid() {
        
        this->exists_plant = false;
        this->exists_zombie = false;
        this->plant = nullptr;
        this->zombie = vector<int>();
        this->zombie.reserve(100);
    }
    ~grid() {
        if(this->plant != nullptr)
        {
            delete this->plant;
            this->plant = nullptr;
        }
        this->zombie.clear();
        this->zombie.swap(this->zombie);
    }
    //检查并获取是否存在植物
    bool get_exists_plant() {
        return this->exists_plant;
    }
    //检查并获取是否存在僵尸
    bool get_exists_zombie() {
        if (this->zombie.empty()) {
            this->exists_zombie = false;
        }
        else {
            this->exists_zombie = true;
        }
        return this->exists_zombie;
    }
    //植物存在状态调整
    void plant_clear() {
        delete this->plant;
        this->plant = nullptr;
        this->exists_plant = false;
    };
    //僵尸存在状态调整
    void zombie_clear() {
        this->exists_zombie = false;
        this->zombie.clear();
        this->zombie.swap(this->zombie);
    };
    //（因死亡或移动）移除格子内某一僵尸
    void zombie_remove(int k) {
        this->zombie.erase(zombie.begin()+k);
    }
    //（因移动）增加格子内的僵尸
    void zombie_append(int id) {
        this->zombie.push_back(id);
    }
    //种植物函数
    bool PlacePlant(plants* plant) {
        if (this->exists_plant || plant == nullptr)
            return false;
        this->plant = plant;
        this->exists_plant = true;
        return true;
    }
    //放置僵尸函数
    bool PlaceZombie(int id) {
        if (id == -1)
            return false;
        this->zombie.push_back(id);
        this->exists_zombie = true;
        return true;
    }
    //得到目前格子内的植物
    plants* GetThisGridPlant() {
        // if(this->plant == nullptr)
        //     return NOPLANT;
        return plant;
    }
    //得到目前格子内的僵尸
    vector<int> GetThisGridZombie() {
        // if(this->zombie.empty())
        //     return NOZOMBIE;
        return zombie;
    }
};

//场地
class field {
protected:
    int rows; //战场格子的总行数
    int columns; //战场格子的总列数
    int plants_num; //场上的植物总数
    int zombies_num; //场上的僵尸总数
    
public:
    unordered_map<int, zombies*>allZombies;
    vector<int>FallRecord;
    int BrokenLinesScores;
    int NotBrokenLinesNum;
    int KillPlantsScores;
    int KillZombiesScores;
    int ZombieGetSun;
    int PlantGetSun;
    int LeftPlants;
    grid** grids; //grid类的二维数组
    //默认构造函数
    field(int rows = 5, int columns = 10, int plants_num = 0, int zombies_num = 0) {
        this->rows = rows;
        this->columns = columns;
        this->plants_num = plants_num;
        this->zombies_num = zombies_num;
        BrokenLinesScores = 0;
        NotBrokenLinesNum = 5;
        KillZombiesScores = 0;
        KillPlantsScores = 0;
        LeftPlants = 0;
        ZombieGetSun = 0;
        PlantGetSun = 0;
        this->grids = new grid * [this->rows];
        FallRecord = vector<int>(rows, 1);
        for (int i = 0; i < this->rows; i++)
        {
            this->grids[i] = new grid[this->columns];
        }
    }
    ~field() {
        for(int i = 0; i < rows; i++)
        {
            delete[] grids[i];
        }
        delete[] grids;
        for(auto&i:allZombies)
        {
            delete i.second;
        }
    }
    //在指定位置种植物函数
    bool PlacePlant(int y, int x, plants* plant) {
        bool IsPlaced = grids[y][x].PlacePlant(plant);
        if (IsPlaced) {
            plants_num++;
        }
        return IsPlaced;
    }
    //在指定列放置僵尸函数
    bool PlaceZombie(int y, zombies* zombie) {
        if (zombie == nullptr)
            return false;
        bool IsPlaced = grids[y][this->columns - 1].PlaceZombie(zombie->getIndex());
        if (IsPlaced) {
            zombies_num++;
            allZombies.insert({ zombie->getIndex(), zombie });
        }
        return IsPlaced;
    }
    bool RemovePlant(int x, int y)
    {
        if (!grids[x][y].get_exists_plant() || grids[x][y].get_exists_zombie())
            return false;
        plants_num--;
        grids[x][y].plant_clear();
        return true;
    }
    //得到行数
    int GetRows()
    {
        return rows;
    }
    //得到列数
    int GetColumns()
    {
        return columns;
    }
    //得到僵尸数量
    int GetZombiesnum() {
        return zombies_num;
    }
    //得到植物数量
    int GetPlantsnum() {
        return plants_num;
    }
    //行僵尸删除操作
    void Zombies_rowclear(int i) {
        for (int j = 0; j < columns; j++) {
            zombies_num -= grids[i][j].GetThisGridZombie().size();
            grids[i][j].zombie_clear();
        };
    };

    //行植物删除操作
    void Plants_rowclear(int i) {
        for (int j = 0; j < columns; j++) {
            plants_num -= grids[i][j].get_exists_plant();
        	grids[i][j].plant_clear();
        };
    };

    //僵尸移动,此处数组传递是为了表示哪行被攻陷
    void Zombie_move(int t) {
        for (int i = 0; i < rows; i++)
        {
            if(FallRecord[i] == 0)
            {
	            continue;
            }
            for (int j = 0; j < columns; j++)
            {
                vector<int> zombies = grids[i][j].GetThisGridZombie();
                int m = 0;
                //这里假设得到的是父类型
                for (int k = 0; k < zombies.size(); k++)
                {
                    int type = allZombies[zombies[k]]->getZombie_Type();
                    if (type == POLEVAULT)
                    {
                        PolevaultZombies* temp = dynamic_cast<PolevaultZombies*> (allZombies[zombies[k]]);
                        if (grids[i][j].get_exists_plant() && temp->get_Ifpole())
                        {
                            temp->Pole();
                            grids[i][j].get_exists_zombie();
                            if (j > 0)
                            {
                                grids[i][j - 1].zombie_append(temp->getIndex());
                                grids[i][j - 1].get_exists_zombie();
                                grids[i][j].zombie_remove(k - m);
                                m++;
                            }
                            else
                            {
                                //这一行被攻陷，同时僵尸消失？
                                BrokenLinesScores += (1000 + (int)(ENDTIME - t));//对应分数更新，下同
                                NotBrokenLinesNum--;
                                Plants_rowclear(i);
                                Zombies_rowclear(i);
                                FallRecord[i] = 0;//0或1皆可，表示该行已沦陷
                                break;
                                
                            }
                        }
                        else if (!grids[i][j].get_exists_plant())
                        {
                            allZombies[zombies[k]]->move();
                            if (allZombies[zombies[k]]->getx() < j)
                            {
                                if (j > 0)
                                {
                                    grids[i][j - 1].zombie_append(zombies[k]);
                                    grids[i][j - 1].get_exists_zombie();
                                    grids[i][j].zombie_remove(k - m);
                                    m++;
                                }
                                else {
                                    //这一行被攻陷，同时僵尸消失？
                                    BrokenLinesScores += (1000 + (int)(ENDTIME - t));//对应分数更新，下同
                                    NotBrokenLinesNum--;
                                    Zombies_rowclear(i);
                                    Plants_rowclear(i);
                                    FallRecord[i] = 0;//0或1皆可，表示该行已沦陷
									break;
                                }
                            }
                        }
                    }
                    else
                    {
                        if (!grids[i][j].get_exists_plant())
                        {
                            allZombies[zombies[k]]->move();
                            if (allZombies[zombies[k]]->getx() < j)
                            {
                                if (j > 0)
                                {
                                    grids[i][j - 1].zombie_append(zombies[k]);
                                    grids[i][j - 1].get_exists_zombie();
                                    grids[i][j].zombie_remove(k - m);
                                	m++;
                                }
                                else {
                                    //这一行被攻陷，同时僵尸消失？
                                    BrokenLinesScores += (1000 + (int)(ENDTIME - t));//对应分数更新，下同
                                    NotBrokenLinesNum--;
                                    Zombies_rowclear(i);
                                    Plants_rowclear(i);
                                    FallRecord[i] = 0;//0或1皆可，表示该行已沦陷
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }



    void Zombies_check(int t) {//检查僵尸血量并删除负血量僵尸
        int HP;
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                vector<int> this_zombies = this->grids[i][j].GetThisGridZombie();//获得当前格子的僵尸集合
                int m = 0;
                for (int k = 0; k < this_zombies.size(); k++) {
                    zombies* this_zombie = allZombies[this_zombies[k]];
                    HP = this_zombie->getHP();
                    if (HP <= 0) {
                        KillZombiesScores += this_zombie->getSun();
                        
                        this->grids[i][j].zombie_remove(k - m);
                        m++;
                        this->zombies_num -= 1;
                    }
                    else {
                        this_zombie->Improve(t);
                        this_zombie->unfrozen();
                    }
                };
                if (this_zombies.empty()) {
                    this->grids[i][j].zombie_clear();
                }
            };
        };


    };
    void Plants_check() {//检查植物血量并删除负血量植物
        int HP;
		
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                plants* this_plant = this->grids[i][j].GetThisGridPlant();//获得当前格子的植物
                if(this_plant == nullptr)
                    continue;
                HP = this_plant->getHP();
                if (HP <= 0) {
                    KillPlantsScores += this_plant->getSun();
                    ZombieGetSun += (int)this_plant->getSun()/5 + (int)sqrt(this_plant->GetOrignalHP());
                    this->grids[i][j].plant_clear();
                    this->plants_num -= 1;
                };
            };
        };
    };

    //条件判断，所有的植物能否攻击到所有的僵尸，如果能则调用攻击函数
    void p_condition_z(string filename) {
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                plants* p = this->grids[i][j].GetThisGridPlant();
                if (p!=nullptr && p->get_able_attack())//能够攻击
                {
                    PlantType plant_type = p->getPlant_Type();
                    switch (plant_type) {
                    case SUNFLOWER: {
                        Sunflower* sunFlower = dynamic_cast<Sunflower*>(p);
                        if (sunFlower->get_able_attack())
                            sunFlower->attack();
                        PlantGetSun += sunFlower->getSun_Produce();
                        break;
                    }
                    case WINTERPEASHOOTER: {
                        for (int k = j; k < this->columns; k++) {
                            if (this->grids[i][k].get_exists_zombie()) {
                                vector<int> zombies = this->grids[i][k].GetThisGridZombie();//获取该格的僵尸
                                int nearest = 0;
                                for (int iter = 0; iter < zombies.size(); iter++) {
                                    if (allZombies[zombies[iter]]->getfx() < allZombies[zombies[nearest]]->getfx())
                                        nearest = iter;
                                }
                                p_attack_z(p, allZombies[zombies[nearest]], filename);
                                allZombies[zombies[nearest]]->frozen();
                                break;//结束遍历行循环
                            }
                        }
                        break;
                    }
                    case PEASHOOTER: {
                        for (int k = j; k < this->columns; k++) {
                            if (this->grids[i][k].get_exists_zombie()) {
                                vector<int> zombies = this->grids[i][k].GetThisGridZombie();//获取该格的僵尸
                                int nearest = 0;
                                for (int iter = 0; iter < zombies.size(); iter++) {
                                    if (allZombies[zombies[iter]]->getfx() < allZombies[zombies[nearest]]->getfx())
                                        nearest = iter;
                                }
                                p_attack_z(p, allZombies[zombies[nearest]], filename);
                                break;//结束遍历行循环
                            }
                        }
                        break;
                    }
                    case SMALLNUT: {
                        break;
                    }
                    case PEPPER: {
                        p->attack();
                        for (int k = 0; k < this->columns; k++) {
                            if (this->grids[i][k].get_exists_zombie()) {
                                vector<int> zombies = this->grids[i][k].GetThisGridZombie();//获取该格的僵尸
                                for (int iter = 0; iter < zombies.size(); iter++) {
                                    p_attack_z(p, allZombies[zombies[iter]], filename);
                                }
                            }
                        }
                        break;
                    }
                    case SQUASH: {
                        vector<int> zombies = this->grids[i][j].GetThisGridZombie();
                        if (zombies.size() != 0) {
                            for (int iter = 0; iter < zombies.size(); iter++) {
                                p_attack_z(p, allZombies[zombies[iter]], filename);
                            }
                        }
                        break;
                    }
                    default: break;
                    }//endswitch
                }//endif

            }
        }
    }

    //条件判断，所有僵尸能否攻击所有植物，如果能则调用攻击函数
    void z_condition_p(string filename) {
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                vector<int> this_zombie = this->grids[i][j].GetThisGridZombie();//获取该格的僵尸 
                plants* p = this->grids[i][j].GetThisGridPlant();
                // zombies this_zombie; = zombies[h];
                // this_zombie = zombies[h]; 
                if (!this_zombie.empty() && p != nullptr)//植物和僵尸在一个格子里则能够攻击
                {
                    for (int h = 0; h < this_zombie.size(); h++) {
                        ZombieType zombie_type = allZombies[this_zombie[h]]->getZombie_Type();
                        z_attack_p(allZombies[this_zombie[h]], p, filename);
                    }
                }//endif   
            }
        }
        return;
    }

    //植物攻击僵尸调用函数；如果僵尸死亡（z_hp<0），需要在函数外（主程序内）处理，delete对应指针；这里已经完成了输出到attack.txt的功能
    int p_attack_z(plants* p, zombies* z, string filename) {
        int z_hp = z->getHurt(p->getDPS());
        p->attack();
        fstream attack_file;
        attack_file.open(filename, ios::app);
        string str = std::to_string(p->getIndex());
        str = str + ' ' + std::to_string(z->getIndex());
        attack_file << str << endl;
        return z_hp;
    };

    //僵尸攻击植物调用函数；如果植物死亡（p_hp<0），需要在函数外（主程序内）处理，delete对应指针；这里已经完成了输出到attack.txt的功能
    int z_attack_p(zombies* z, plants* p, string filename) {
	    int dps = z->getDPS();
        int p_hp = p->getHurt(dps);
        fstream attack_file;
        attack_file.open(filename, ios::app);
        string str = std::to_string(z->getIndex());
        str = str + ' ' + std::to_string(p->getIndex());
        attack_file << str << endl;
        return p_hp;
    };

    //每回合更新所有植物的攻击间隔；种植和放置间隔另作处理
    void renew_CD() {
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                if (this->grids[i][j].get_exists_plant()) {
                    plants* p = this->grids[i][j].GetThisGridPlant();
                    p->renew_attack_CD();//更新植物攻击CD
                    // p->renew_plant_CD();//更新植物种植CD     
                }
            }
        }
        ZombieGetSun = 0;
        PlantGetSun = 0;
    }

    void getLeftPlants() {
        int LeftLines = 0;
        for (int i = 0; i < rows; i++) {
            if (FallRecord[i] == 1) {
                LeftLines++;
                for (int j = 0; j < columns; j++) {
                    if (grids[i][j].get_exists_plant())
                        LeftPlants++;
                }
            }
        }
    }
};



#endif// !FIELD_H