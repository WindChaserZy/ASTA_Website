#ifndef COMMANDLIST_H_
#define COMMANDLIST_H_
#include <vector>
using std::vector;
struct PlantCommand
{
    int m_plant;
    int x;
    int y;
};

struct ZombieCommand
{
    int m_zombie;
    int y;
};

class CommandList
{
public:
    CommandList()
    {
        PlacedPlant.resize(6, 0);
        PlacedZombie.resize(5, 0);
    }
    void addCommand(int plantname, int x, int y)  //°æFC19°ø÷÷÷≤÷≤ŒÔ√¸¡Ó
    {
            PlantCommand this_step = { plantname,x,y };
            plant_commands.push_back(this_step);
    }
    void addCommand(int zombiename, int y)            //°æFC19°ø∑≈Ω© ¨√¸¡Ó
    {
            ZombieCommand this_step = { zombiename,y };
            zombie_commands.push_back(this_step);
    }

    std::vector<PlantCommand> getPlantCommands() {
        return plant_commands;
    }
    vector<ZombieCommand> getZombieCommands() {
        return zombie_commands;
    }
    void clearPlantCommands() {
        plant_commands.clear();
    }
    void clearZombieCommands() {
        zombie_commands.clear();
    }
    void renew() {
        for(int i = 0; i < 6; i++)
        {
            PlacedPlant[i] = 0;
        }
        for(int i = 0; i < 5; i++)
        {
            PlacedZombie[i] = 0;
        }
    }
private:
    vector<PlantCommand> plant_commands;
    vector<ZombieCommand> zombie_commands;
    vector<int> PlacedPlant;
    vector<int> PlacedZombie;
};
#endif