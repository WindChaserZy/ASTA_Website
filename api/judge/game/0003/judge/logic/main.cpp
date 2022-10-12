#include "Plants.h"
#include "Zombies.h"
#include "Game.h"
#include "Field.h"
#include <iostream>
#include <fstream>

#include "Player.h"
#include "player_code.h"
#include <dirent.h>
#include <ctime>
#ifdef _DEBUG

#define new  new(_NORMAL_BLOCK, __FILE__, __LINE__)

#endif
using std::cout;
using std::endl;
using namespace DAGAN;


//�ٶ�ѡ����д���ļ���Ϊplayer_ai.h,�ɲ�ȡ������ʽ����
// Dlltest.h
// #pragma comment(lib��"MyDll.lib")
// extern "C"_declspec(dllimport) int Max(int a,int b);
// extern "C"_declspec(dllimport) int Min(int a,int b);
// //TestDll.cpp
// #include
// #include"Dlltest.h"
// void main()
// {int a;
// a=min(8,10)
// printf("�ȽϵĽ��Ϊ%d/n"��a);
// }

//ȫ�ֱ�����ÿ�����ֻ��һ��
unsigned int Game::time = 0;
unsigned int Game::index = 1;
struct rankcmp {
    int PlayerID; //ѡ��ID
    int Score; //ѡ�ֵ÷�
    int BrokenLines; //ѡ����Ϊ��ʬ����������
    int NotBrokenLines; //ѡ����Ϊֲ�﷽δ��������
    int KillPlants; //ѡ����Ϊ��ʬ����ɱ��ֲ����
    int KillZombies; //ѡ����Ϊֲ�﷽��ɱ�Ľ�ʬ��
    bool operator<(const rankcmp& p) { //��������
        if (Score != p.Score)
            return Score > p.Score;
        if (BrokenLines != p.BrokenLines)
            return BrokenLines > p.BrokenLines;
        if (NotBrokenLines != p.NotBrokenLines)
            return NotBrokenLines > p.NotBrokenLines;
        if (KillPlants != p.KillPlants)
            return KillPlants > p.KillPlants;
        if (KillZombies > p.KillZombies)
            return KillZombies > p.KillZombies;
        return rand() % 2 == 1; //�������ݾ���ͬʱ����������Ƿ�Ϊ1����
    }
};
//�����Action.txt��
void Action_out(Game game, string filename) {
    int step = Game::getTime();
    fstream action_file;
    action_file.open(filename, ios::app);
    vector<vector<int>>PlantCommands = game.new_Plants;
    vector<vector<int>>ZombieCommands = game.new_Zombies;
    vector <vector<int>> RemoveCommads = game.removed_plants;
    //step
    action_file << step << endl;
    //ֲ����ҵĲ�����
    action_file << PlantCommands.size() << endl;
    //��ʬ��ҵĲ�����
    action_file << ZombieCommands.size() << endl;
    //action_file << RemoveCommads.size() << endl;
    //ֲ����ҵĲ��� x y type
    for (auto& i : PlantCommands) {
        action_file << i[0] << ' ' << i[1] << ' ' << i[2] << ' ';
        switch (i[3])
        {
        case SUNFLOWER:
            action_file << "SunFlower" << endl;
            break;
        case WINTERPEASHOOTER:
            action_file << "SnowPea" << endl;
            break;
        case PEASHOOTER:
            action_file << "Peashooter" << endl;
            break;
        case SMALLNUT:
            action_file << "WallNut" << endl;
            break;
        case PEPPER:
            action_file << "Jalapeno" << endl;
            break;
        case SQUASH:
            action_file << "Squash" << endl;
            break;
        default:
            action_file << endl;
            break;
        }
    }
    
    //��ʬ��ҵĲ��� y type
    for (auto& i : ZombieCommands) {
        action_file << i[0] << ' ' << i[1] << ' ';
        switch (i[2])
        {
        case NORMAL:
            action_file << "Zombie" << endl;
            break;
        case BUCKET:
            action_file << "BucketheadZombie" << endl;
            break;
        case POLEVAULT:
            action_file << "PoleVaultingZombie" << endl;
            break;
        case SLED:
            action_file << "Zomboni" << endl;
            break;
        case GARGANTUAR:
            action_file << "Gargantuar" << endl;
            break;
        default:
            break;
        }
    }
    /*
    for (auto& i : RemoveCommads)
    {
        action_file << i[0] << ' ' << i[1] << ' ' << i[2] << endl;
    }
    */
    action_file << endl;
}


//�ڹ�������������������������main.cpp�����������step
void Attack_out(Game game, string filename) {
    fstream attack_file;
    int step = Game::getTime();
    attack_file.open(filename, ios::app);
    attack_file << step << endl;
    //step

    //����������������Ӧ�����ֲ��ͽ�ʬ�������ж������
    //�����ߺͱ�������
    
    game.Field->p_condition_z(filename);
    game.Field->Plants_check();
    game.Field->Zombies_check(Game::getTime());
    game.Field->z_condition_p(filename);
    game.Field->Plants_check();
    game.Field->Zombies_check(Game::getTime());
    attack_file << endl;
}



//ȷ�����ж���״̬�������State.txt��
void State_out(Game game, string filename) {
    int step = Game::getTime();
    fstream state_file;
    field* m_field = game.Field;
    PlantCamp* PC = dynamic_cast<PlantCamp*>(game.GetPlantCamp());
    ZombieCamp* ZC = dynamic_cast<ZombieCamp*>(game.GetZombieCamp());
    state_file.open(filename, ios::app);
    int row = m_field->GetRows();//�������
    int column = m_field->GetColumns();//�������
    int plantsnum = m_field->GetPlantsnum(); //���ֲ������
    int zombiesnum = m_field->GetZombiesnum();//��ý�ʬ����
    grid** m_grids = m_field->grids;
    //�����ǰ��step
    state_file << step << endl;
    //����ִ�ֲ�ｩʬ����
    state_file << m_field->GetPlantsnum() << endl;
    state_file << m_field->GetZombiesnum() << endl;
    //ֲ�ｩʬ��Ӫʣ������
    state_file << PC->getSun() << endl;
    state_file << ZC->getSun() << endl;
    //����ֲ�ｩʬʣ����ֲcd
    int* PlantCD = PC->getPlantCD();
    int* ZombieCD = ZC->getPlantCD();
    state_file << PlantCD[0] <<" " <<  PlantCD[1]  << " " << PlantCD[2] << " " << PlantCD[3] << " " << PlantCD[4] << " " << PlantCD[5] << endl;
    state_file << ZombieCD[0] << " " << ZombieCD[1] << " " << ZombieCD[2] <<" " << ZombieCD[3] <<" "<< ZombieCD[4] << endl;
    //�������������и���,���ֲ��״̬��
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            plants* this_plant = m_grids[i][j].GetThisGridPlant();//��õ�ǰ���ӵ�ֲ��
           //  index     Type(str)      Location(x, y)
            if (this_plant == nullptr) {
                continue;
            }
            PlantType this_type = this_plant->getPlant_Type();

            //NOPLANT = 0, SUNFLOWER, WINTERPEASHOOTER, PEASHOOTER, SMALLNUT, PEPPER, SQUASH
            switch (this_type) {
            case 0: break;
            case 1: {
                Sunflower* the_plant = dynamic_cast<Sunflower*>(this_plant);
                //������Ҫ�õ�ȫ��ʱ���ȥֲ����ֲ�ĳ�ʼʱ�̡�
                //bool if_producesun = int(the_plant ->getTime_plant()) / the_plant->get
                state_file <<this_plant->getIndex() << " SunFlower" << ' ' << this_plant->getx() << ' ' << this_plant->gety() << " " << this_plant->getHP();
                if (the_plant->IfProduced) {
                    state_file << " True\n";
                    the_plant->IfProduced = false;
                }
                else
                    state_file << " False\n";
                break;
            }
            case 2: {
                state_file << this_plant->getIndex() << " SnowPea" << ' ' << this_plant->getx() << ' ' << this_plant->gety() << " " << this_plant->getHP() << endl;
                break;
            }
            case 3: {
                state_file << this_plant->getIndex() << " Peashooter" << ' ' << this_plant->getx() << ' ' << this_plant->gety() << " " << this_plant->getHP() << endl;
                break;
            }
            case 4: {
                state_file << this_plant->getIndex() << " WallNut" << ' ' << this_plant->getx() << ' ' << this_plant->gety() << " " << this_plant->getHP() << endl;
                break;
            }
            case 5:{
                state_file << this_plant->getIndex() << " Jalapeno" << ' ' << this_plant->getx() << ' ' << this_plant->gety() << " " << this_plant->getHP() << endl;
                break;
	            }
            case 6:
	            {
                state_file << this_plant->getIndex() << " Squash" << ' ' << this_plant->getx() << ' ' << this_plant->gety() << " " << this_plant->getHP() << endl;
                break;
	            }
            }
        }
    }
    //�������������и���,�����ʬ״̬��
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            vector<int> this_zombies = m_grids[i][j].GetThisGridZombie();//��õ�ǰ���ӵĽ�ʬ����
            for (int k = 0; k < this_zombies.size(); k++) {
                zombies* this_zombie = game.Field->allZombies[this_zombies[k]];
                ZombieType this_type = this_zombie->getZombie_Type();

                //NOZOMBIE = 0, NORMAL, BUCKET, POLEVAULT, SLED, GARGANTUAR
                switch (this_type) {
                case 0: break;
                case 1: {
                    state_file << this_zombie->getIndex() << " Zombie" << ' ' << this_zombie->getfx() << ' ' << this_zombie->gety() << " " << this_zombie->getHP() << endl;
                    break;
                }
                case 2: {
                    BucketZombies* the_zombie = dynamic_cast<BucketZombies*>(this_zombie);
                    state_file << this_zombie->getIndex() << " BucketheadZombie" << ' ' << this_zombie->getfx() << ' ' << this_zombie->gety() << " " << the_zombie->Bucket() << " " << this_zombie->getHP() << endl;
                    break;
                }
                case 3: {
                    PolevaultZombies* the_zombie = dynamic_cast<PolevaultZombies*>(this_zombie);
                    state_file << this_zombie->getIndex() << " PoleVaultingZombie" << ' ' << this_zombie->getfx() << ' ' << this_zombie->gety()  << " " << this_zombie->getHP();
                        if(the_zombie->get_Ifpole())
                        {
                            state_file << " True\n";
                        }
                        else
                        {
                            state_file << " False\n";
                        }
                    break;
                }
                case 4: {
                    state_file << this_zombie->getIndex() << " Zomboni" << ' ' << this_zombie->getfx() << ' ' << this_zombie->gety() << " " << this_zombie->getHP() << endl;
                    break;
                }
                case 5: {
                    state_file << this_zombie->getIndex() << " Gargantuar" << ' ' << this_zombie->getfx() << ' ' << this_zombie->gety() << " " << this_zombie->getHP() << endl;
                    break;
                }
                }

            }
        }
    }
    state_file << endl;

}
int main(int argc, char** argv) {
    
    field* now_field = new field;
    Game game(now_field);
    vector<Player_Code>  players;
    vector<string> players_filename(2);//
    vector<string>  players_name(2);
    string config_filename = "config19.ini";
    ifstream ifs(config_filename);
    fstream errstrem("error_log/error.log");
    if (!ifs.is_open())
    {
        errstrem << "Can not open config file.";
        //system("pause");
        return -1;
    }
    for (int i = 0; i < 2; i++) {
        ifs >> players_filename[i];
    }
    PlantCamp* Pcamp = dynamic_cast<PlantCamp*>(game.GetPlantCamp());
    ZombieCamp* Zcamp = dynamic_cast<ZombieCamp*>(game.GetZombieCamp());
    Player* Pplayer = new Player(Pcamp);
    Player* Zplayer = new Player(Zcamp);
    
    for (int i = 0; i < 2; ++i) {
        Player_Code player(players_filename[i], i + 1);
        string player_name;
        if (ifs >> player_name && !player_name.empty())//�˴�ifs���ļ�������
            player.setName(player_name);
        if (player.isValid())                //���ai��all���سɹ��᷵��true
        {
            players.push_back(player);
            players_name.push_back(player_name);
        }
        else {
            players.push_back(player); //ѹ��ȥ��������ʱ���ai�������ValidΪfalse
            //cout << "[Warning] failed to load player_ai " << players_filename[i] << endl;
            player.setName(player.getName() + "//NOT_VALID");
            players_name.push_back(player_name + "[N/A]");

#if (defined _MSC_VER && defined _DEBUG)
            //system("pause");
#endif
#if(defined __GNUC__ && defined _DEBUG)
            getchar();
#endif
        }
    }
    //cout << "Round1 begin.\n";
    //���������лغ���ѭ������һ�غϣ�
    Pplayer->setNotBrokenLinesNum(5);
    string DirPath = string("record");
    fstream f;
    f.open(DirPath+"/round1/state.txt", ios::app);
    f << game.Field->GetRows() << ' ' << game.Field->GetColumns() << endl;
    while (Game::getTime() < ENDTIME && game.Field->NotBrokenLinesNum != 0) {
    	Game::AddTime();
        if(Game::getTime() % 500 == 0)
        {
            Zcamp->addSun(200);
            Zcamp->LastPlaceZombie = { 0, 0, 0, 0, 0 };
        }
#ifdef _DEBUG
        //cout << "LeftLines: " << game.Field->NotBrokenLinesNum << endl;
        //cout << "Step: " << Game::getTime() << endl;
        //cout << Pplayer->getScore() << " " << Zplayer->getScore() << endl;
        //cout << Pplayer->Camp->getSun() << " " << Zplayer->Camp->getSun() << endl;
#endif
        game.Field->renew_CD();//ÿ�غϸ���cd
        game.new_Zombies.clear();
        game.new_Plants.clear();
        game.removed_plants.clear();
        Pplayer->commands.renew();
        Zplayer->commands.renew();
        Pplayer->commands.clearPlantCommands();
        Zplayer->commands.clearZombieCommands();
        
        players[0].run(Pplayer);
        players[1].run(Zplayer);
        
        int ProvideSun = Game::getTime() / 200 + 1;
        Zcamp->addSun(ProvideSun);
        
        State_out(game, DirPath + "/round1/state.txt");
        Attack_out(game, DirPath + "/round1/attack.txt");
        game.Field->Zombie_move(Game::getTime());
        for (auto& i : Pplayer->commands.getPlantCommands()) {
            if (i.m_plant != -1) {
                if (Pcamp->PlacePlant(i.x, i.y, i.m_plant))
                {
                    game.new_Plants.push_back({ (int)Game::index - 1, i.x, i.y, i.m_plant });
                }
            }
            else
            {
                if (game.Field->grids[i.x][i.y].get_exists_plant()) {
                    int index = game.Field->grids[i.x][i.y].GetThisGridPlant()->getIndex();
                    if (Pcamp->RemovePlant(i.x, i.y))
                    {
                        game.removed_plants.push_back({ index, i.x, i.y });
                    }
                    
                }
            }
        }
        for (auto& i : Zplayer->commands.getZombieCommands()) {
            if(Zcamp->PlaceZombie(i.y, i.m_zombie))
            {
                game.new_Zombies.push_back({ (int)Game::index - 1, i.y, i.m_zombie});
            }

        }
        Action_out(game, DirPath + "/round1/action.txt");
#ifdef _DEBUG
        
        int** Plants = Pplayer->Camp->getCurrentPlants();
        int*** Zombies = Pplayer->Camp->getCurrentZombies();
        int* PCD = Pplayer->Camp->getPlantCD();
        int* ZCD = Zplayer->Camp->getPlantCD();
        for(int i = 0; i < 6; i++)
        {
            //cout << PCD[i] << ' ';
        }
        //cout << "\n";
        for(int i = 0; i < 5; i++)
        {
            //cout << ZCD[i] << ' ';
        }
        //cout << '\n';
        for (int i = 0; i < game.Field->GetRows(); i++)
        {
            for (int j = 0; j < game.Field->GetColumns(); j++)
            {
                //cout << Plants[i][j] << ":";
                if (Plants[i][j] == 0)
                {
                    //cout << "0 ";
                }
                else
                {
                    //cout << game.Field->grids[i][j].GetThisGridPlant()->getHP() << " ";
                }
            }
            //cout << endl;
        }
        for (int i = 0; i < game.Field->GetRows(); i++)
        {
            for (int j = 0; j < game.Field->GetColumns(); j++)
            {
                int k = 0;
                //cout << "(";
                while (Zombies[i][j][k] != -1)
                {
                    //cout << Zombies[i][j][k] << ":" << game.Field->grids[i][j].GetThisGridZombie()[k]->getHP() << ":" << game.Field->grids[i][j].GetThisGridZombie()[k]->getDPS() << ":" << game.Field->grids[i][j].GetThisGridZombie()[k]->getspeed();
                    if(Zombies[i][j][k] == 2)
                    {
                        BucketZombies* t = dynamic_cast<BucketZombies*>(game.Field->grids[i][j].GetThisGridZombie()[k]);
                        //cout << ":" << t->Bucket();
                    }
                    //cout << " ";
                    k++;
                }
                //cout << ") ";
            }
            //cout << endl;
        }
#endif
        Zcamp->addSun(game.Field->ZombieGetSun);
        Pcamp->addSun(game.Field->PlantGetSun);
        Zplayer->setKillPlants(game.Field->KillPlantsScores);
        Pplayer->setKillZombies(game.Field->KillZombiesScores);
        Zplayer->setBrokenLines(game.Field->BrokenLinesScores);
        Pplayer->setScore(Pplayer->getKillZombiesScore());
        Zplayer->setScore(Zplayer->getKillPlantsScore() + Zplayer->getBrokenLinesScore());
        Pplayer->setNotBrokenLinesNum(game.Field->NotBrokenLinesNum);
    }
    now_field->getLeftPlants();
    Pplayer->setScore( Pplayer->getScore() + 1000 * Pplayer->getNotBrokenLines() + now_field->LeftPlants * 100);
    int Round1PScore = Pplayer->getScore();
    int Round2ZScore = Zplayer->getScore();
    //cout << "Round1 End.\n" << "Player1's score: " << Pplayer->getScore() << " Player2's score: " << Zplayer->getScore() << endl;
#if (defined _MSC_VER)
    //system("pause");
#endif
#if(defined __GNUC__)
    //getchar();
#endif
    game.restart();
    
    delete Pcamp;
    delete Zcamp;
    delete now_field;
    now_field = nullptr;
    Pcamp = nullptr;
    Zcamp = nullptr;
    now_field = new field();
    Player* tempP = Pplayer;
    Pplayer = Zplayer;
    Zplayer = tempP;
    Pplayer->setNotBrokenLinesNum(5);
    game.setField(now_field);
    Pcamp = dynamic_cast<PlantCamp*> (game.GetPlantCamp());
    Zcamp = dynamic_cast<ZombieCamp*>(game.GetZombieCamp());
    Pplayer->setCamp(Pcamp);
    Zplayer->setCamp(Zcamp);
    f.close();
    f.open(DirPath + "/round2/state.txt", ios::app);
    f << game.Field->GetRows() << ' ' << game.Field->GetColumns() << endl;
    //cout << "Round2 begin.\n";
    while (Game::getTime() < ENDTIME && game.Field->NotBrokenLinesNum != 0) {
        Game::AddTime();
        if (Game::getTime() % 500 == 0)
        {
            Zcamp->addSun(200);
            Zcamp->LastPlaceZombie = { 0, 0, 0, 0, 0 };
        }
#ifdef _DEBUG
        //cout << "LeftLines: " << game.Field->NotBrokenLinesNum << endl;
        //cout << "Step: " << Game::getTime() << endl;
        //cout << Pplayer->getScore() << " " << Zplayer->getScore() << endl;
        //cout << Pplayer->Camp->getSun() << " " << Zplayer->Camp->getSun() << endl;
#endif
        game.Field->renew_CD();//ÿ�غϸ���cd
        game.new_Zombies.clear();
        game.new_Plants.clear();
        Pplayer->commands.renew();
        Zplayer->commands.renew();
        Pplayer->commands.clearPlantCommands();
        Zplayer->commands.clearZombieCommands();

        players[0].run(Zplayer);
        players[1].run(Pplayer);

        int ProvideSun = Game::getTime() / 200 + 1;
        Zcamp->addSun(ProvideSun);

        State_out(game, DirPath + "/round2/state.txt");
        Attack_out(game, DirPath + "/round2/attack.txt");
        game.Field->Zombie_move(Game::getTime());
        for (auto& i : Pplayer->commands.getPlantCommands()) {
            if (i.m_plant != -1) {
                if (Pcamp->PlacePlant(i.x, i.y, i.m_plant))
                {
                    game.new_Plants.push_back({ (int)Game::index - 1, i.x, i.y, i.m_plant });
                }
            }
            else
            {
                Pcamp->RemovePlant(i.x, i.y);
            }
        }
        for (auto& i : Zplayer->commands.getZombieCommands()) {
            if (Zcamp->PlaceZombie(i.y, i.m_zombie))
            {
                game.new_Zombies.push_back({ (int)Game::index - 1, i.y, i.m_zombie });
            }

        }
        Action_out(game, DirPath + "/round2/action.txt");

#ifdef _DEBUG

        int** Plants = Pplayer->Camp->getCurrentPlants();
        int*** Zombies = Pplayer->Camp->getCurrentZombies();
        int* PCD = Pplayer->Camp->getPlantCD();
        int* ZCD = Zplayer->Camp->getPlantCD();
        for (int i = 0; i < 6; i++)
        {
            //cout << PCD[i] << ' ';
        }
        //cout << "\n";
        for (int i = 0; i < 5; i++)
        {
            //cout << ZCD[i] << ' ';
        }
        //cout << '\n';
        for (int i = 0; i < game.Field->GetRows(); i++)
        {
            for (int j = 0; j < game.Field->GetColumns(); j++)
            {
                //cout << Plants[i][j] << ":";
                if (Plants[i][j] == 0)
                {
                    //cout << "0 ";
                }
                else
                {
                    //cout << game.Field->grids[i][j].GetThisGridPlant()->getHP() << " ";
                }
            }
            //cout << endl;
        }
        for (int i = 0; i < game.Field->GetRows(); i++)
        {
            for (int j = 0; j < game.Field->GetColumns(); j++)
            {
                int k = 0;
                //cout << "(";
                while (Zombies[i][j][k] != -1)
                {
                    //cout << Zombies[i][j][k] << ":" << game.Field->grids[i][j].GetThisGridZombie()[k]->getHP() << ":" << game.Field->grids[i][j].GetThisGridZombie()[k]->getDPS() << ":" << game.Field->grids[i][j].GetThisGridZombie()[k]->getspeed();
                    if (Zombies[i][j][k] == 2)
                    {
                        BucketZombies* t = dynamic_cast<BucketZombies*>(game.Field->grids[i][j].GetThisGridZombie()[k]);
                        //cout << ":" << t->Bucket();
                    }
                    //cout << " ";
                    k++;
                }
                //cout << ") ";
    }
            //cout << endl;
        }
#endif
        Zcamp->addSun(game.Field->ZombieGetSun);
        Pcamp->addSun(game.Field->PlantGetSun);
        Zplayer->setKillPlants(game.Field->KillPlantsScores);
        Pplayer->setKillZombies(game.Field->KillZombiesScores);
        Zplayer->setBrokenLines(game.Field->BrokenLinesScores);
        Pplayer->setScore(Pplayer->getKillZombiesScore() + Round2ZScore);
        Zplayer->setScore(Zplayer->getKillPlantsScore() + Zplayer->getBrokenLinesScore() + Round1PScore);
        Pplayer->setNotBrokenLinesNum(game.Field->NotBrokenLinesNum);
    }
    now_field->getLeftPlants();
    Pplayer->setScore(Pplayer->getScore() + 1000 * Pplayer->getNotBrokenLines() + now_field->LeftPlants * 100);
    printf("%d %d \n", Zplayer->getScore(), Pplayer->getScore());
    fflush(stdout);
    //cout << "Round2 End.\n" << "Player1's score: " << Zplayer->getScore() << " Player2's score: " << Pplayer->getScore() << endl;
    //system("pause");
    delete Pcamp;
    delete Zcamp;
    delete now_field;
    return 0;
}

//�����жϺ͹�������д��Field.h��






//��ʬ�ƶ�����ʬ�ƶ�д�ڽ�ʬ�����棻����Ľ�ʬ�ƶ�д��Field.h��

//ֲ����ֲʱ�䣺ÿһ֡��ֲʱ���һ��


//�����ж��Ƿ��ɹ�����������ɹ�����������ù���������ͬʱ�����attack.txt�����������������ڼ�ĳ��������������ʵʱ������deleteʵ�����󣩣�
//



