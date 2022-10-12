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
const int ENDTIME = 2000; //����ʱ��
//�����࣬��Ϊһ�����ӿ���ͬʱ����ֲ��ͽ�ʬ����ʱ��ʬ��ʼ����ֲ��
class grid {
private:
    bool exists_plant;
    bool exists_zombie;
    plants* plant;
    vector<int> zombie;
public:
    //Ĭ�Ϲ��캯������Ϸ��ʼʱ���ã���Ĭ��Ϊ��
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
    //��鲢��ȡ�Ƿ����ֲ��
    bool get_exists_plant() {
        return this->exists_plant;
    }
    //��鲢��ȡ�Ƿ���ڽ�ʬ
    bool get_exists_zombie() {
        if (this->zombie.empty()) {
            this->exists_zombie = false;
        }
        else {
            this->exists_zombie = true;
        }
        return this->exists_zombie;
    }
    //ֲ�����״̬����
    void plant_clear() {
        delete this->plant;
        this->plant = nullptr;
        this->exists_plant = false;
    };
    //��ʬ����״̬����
    void zombie_clear() {
        this->exists_zombie = false;
        this->zombie.clear();
        this->zombie.swap(this->zombie);
    };
    //�����������ƶ����Ƴ�������ĳһ��ʬ
    void zombie_remove(int k) {
        this->zombie.erase(zombie.begin()+k);
    }
    //�����ƶ������Ӹ����ڵĽ�ʬ
    void zombie_append(int id) {
        this->zombie.push_back(id);
    }
    //��ֲ�ﺯ��
    bool PlacePlant(plants* plant) {
        if (this->exists_plant || plant == nullptr)
            return false;
        this->plant = plant;
        this->exists_plant = true;
        return true;
    }
    //���ý�ʬ����
    bool PlaceZombie(int id) {
        if (id == -1)
            return false;
        this->zombie.push_back(id);
        this->exists_zombie = true;
        return true;
    }
    //�õ�Ŀǰ�����ڵ�ֲ��
    plants* GetThisGridPlant() {
        // if(this->plant == nullptr)
        //     return NOPLANT;
        return plant;
    }
    //�õ�Ŀǰ�����ڵĽ�ʬ
    vector<int> GetThisGridZombie() {
        // if(this->zombie.empty())
        //     return NOZOMBIE;
        return zombie;
    }
};

//����
class field {
protected:
    int rows; //ս�����ӵ�������
    int columns; //ս�����ӵ�������
    int plants_num; //���ϵ�ֲ������
    int zombies_num; //���ϵĽ�ʬ����
    
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
    grid** grids; //grid��Ķ�ά����
    //Ĭ�Ϲ��캯��
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
    //��ָ��λ����ֲ�ﺯ��
    bool PlacePlant(int y, int x, plants* plant) {
        bool IsPlaced = grids[y][x].PlacePlant(plant);
        if (IsPlaced) {
            plants_num++;
        }
        return IsPlaced;
    }
    //��ָ���з��ý�ʬ����
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
    //�õ�����
    int GetRows()
    {
        return rows;
    }
    //�õ�����
    int GetColumns()
    {
        return columns;
    }
    //�õ���ʬ����
    int GetZombiesnum() {
        return zombies_num;
    }
    //�õ�ֲ������
    int GetPlantsnum() {
        return plants_num;
    }
    //�н�ʬɾ������
    void Zombies_rowclear(int i) {
        for (int j = 0; j < columns; j++) {
            zombies_num -= grids[i][j].GetThisGridZombie().size();
            grids[i][j].zombie_clear();
        };
    };

    //��ֲ��ɾ������
    void Plants_rowclear(int i) {
        for (int j = 0; j < columns; j++) {
            plants_num -= grids[i][j].get_exists_plant();
        	grids[i][j].plant_clear();
        };
    };

    //��ʬ�ƶ�,�˴����鴫����Ϊ�˱�ʾ���б�����
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
                //�������õ����Ǹ�����
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
                                //��һ�б����ݣ�ͬʱ��ʬ��ʧ��
                                BrokenLinesScores += (1000 + (int)(ENDTIME - t));//��Ӧ�������£���ͬ
                                NotBrokenLinesNum--;
                                Plants_rowclear(i);
                                Zombies_rowclear(i);
                                FallRecord[i] = 0;//0��1�Կɣ���ʾ����������
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
                                    //��һ�б����ݣ�ͬʱ��ʬ��ʧ��
                                    BrokenLinesScores += (1000 + (int)(ENDTIME - t));//��Ӧ�������£���ͬ
                                    NotBrokenLinesNum--;
                                    Zombies_rowclear(i);
                                    Plants_rowclear(i);
                                    FallRecord[i] = 0;//0��1�Կɣ���ʾ����������
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
                                    //��һ�б����ݣ�ͬʱ��ʬ��ʧ��
                                    BrokenLinesScores += (1000 + (int)(ENDTIME - t));//��Ӧ�������£���ͬ
                                    NotBrokenLinesNum--;
                                    Zombies_rowclear(i);
                                    Plants_rowclear(i);
                                    FallRecord[i] = 0;//0��1�Կɣ���ʾ����������
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }



    void Zombies_check(int t) {//��齩ʬѪ����ɾ����Ѫ����ʬ
        int HP;
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                vector<int> this_zombies = this->grids[i][j].GetThisGridZombie();//��õ�ǰ���ӵĽ�ʬ����
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
    void Plants_check() {//���ֲ��Ѫ����ɾ����Ѫ��ֲ��
        int HP;
		
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                plants* this_plant = this->grids[i][j].GetThisGridPlant();//��õ�ǰ���ӵ�ֲ��
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

    //�����жϣ����е�ֲ���ܷ񹥻������еĽ�ʬ�����������ù�������
    void p_condition_z(string filename) {
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                plants* p = this->grids[i][j].GetThisGridPlant();
                if (p!=nullptr && p->get_able_attack())//�ܹ�����
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
                                vector<int> zombies = this->grids[i][k].GetThisGridZombie();//��ȡ�ø�Ľ�ʬ
                                int nearest = 0;
                                for (int iter = 0; iter < zombies.size(); iter++) {
                                    if (allZombies[zombies[iter]]->getfx() < allZombies[zombies[nearest]]->getfx())
                                        nearest = iter;
                                }
                                p_attack_z(p, allZombies[zombies[nearest]], filename);
                                allZombies[zombies[nearest]]->frozen();
                                break;//����������ѭ��
                            }
                        }
                        break;
                    }
                    case PEASHOOTER: {
                        for (int k = j; k < this->columns; k++) {
                            if (this->grids[i][k].get_exists_zombie()) {
                                vector<int> zombies = this->grids[i][k].GetThisGridZombie();//��ȡ�ø�Ľ�ʬ
                                int nearest = 0;
                                for (int iter = 0; iter < zombies.size(); iter++) {
                                    if (allZombies[zombies[iter]]->getfx() < allZombies[zombies[nearest]]->getfx())
                                        nearest = iter;
                                }
                                p_attack_z(p, allZombies[zombies[nearest]], filename);
                                break;//����������ѭ��
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
                                vector<int> zombies = this->grids[i][k].GetThisGridZombie();//��ȡ�ø�Ľ�ʬ
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

    //�����жϣ����н�ʬ�ܷ񹥻�����ֲ����������ù�������
    void z_condition_p(string filename) {
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                vector<int> this_zombie = this->grids[i][j].GetThisGridZombie();//��ȡ�ø�Ľ�ʬ 
                plants* p = this->grids[i][j].GetThisGridPlant();
                // zombies this_zombie; = zombies[h];
                // this_zombie = zombies[h]; 
                if (!this_zombie.empty() && p != nullptr)//ֲ��ͽ�ʬ��һ�����������ܹ�����
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

    //ֲ�﹥����ʬ���ú����������ʬ������z_hp<0������Ҫ�ں����⣨�������ڣ�������delete��Ӧָ�룻�����Ѿ�����������attack.txt�Ĺ���
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

    //��ʬ����ֲ����ú��������ֲ��������p_hp<0������Ҫ�ں����⣨�������ڣ�������delete��Ӧָ�룻�����Ѿ�����������attack.txt�Ĺ���
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

    //ÿ�غϸ�������ֲ��Ĺ����������ֲ�ͷ��ü����������
    void renew_CD() {
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                if (this->grids[i][j].get_exists_plant()) {
                    plants* p = this->grids[i][j].GetThisGridPlant();
                    p->renew_attack_CD();//����ֲ�﹥��CD
                    // p->renew_plant_CD();//����ֲ����ֲCD     
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