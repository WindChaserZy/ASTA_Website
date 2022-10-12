#include "Field.h"
#include "Game.h"
#include "Camp.h"

#include <iostream>



int Camp::getRows()
{
    return Field->GetRows();
}
int Camp::getColumns()
{
    return Field->GetColumns();
}

Camp::Camp(field* _Field, int _sun)
{
    Field = _Field;
    sun = _sun;
    int rows = Field->GetRows();
    int columns = Field->GetColumns();
    currentPlants = new int* [rows];
    currentZombies = new int** [rows];
    leftLines = new int[rows];
    grid** NowGrid = Field->grids;
    for(int i = 0; i < rows; i++)
    {
        leftLines[i] = Field->FallRecord[i];
        currentPlants[i] = new int[columns];
        currentZombies[i] = new int* [columns];
	    for(int j = 0; j < columns; j++)
	    {
            plants* this_plant = NowGrid[i][j].GetThisGridPlant();
            if(this_plant == nullptr)
            {
                currentPlants[i][j] = 0;
            }
            else
            {
                currentPlants[i][j] = this_plant->getPlant_Type();
            }
            vector<int> this_zombies = NowGrid[i][j].GetThisGridZombie();
            currentZombies[i][j] = new int[this_zombies.size() + 1];
            currentZombies[i][j][this_zombies.size()] = -1;
            for(int k = 0; k < this_zombies.size(); k++)
            {
                currentZombies[i][j][k] = Field->allZombies[this_zombies[k]]->getZombie_Type();
            }
	    }
    }
}

int** Camp::getCurrentPlants()
{
    int rows = Field->GetRows(), columns = Field->GetColumns();
    grid** NowGrid = Field->grids;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j <columns; j++)
        {
            plants* this_plant = NowGrid[i][j].GetThisGridPlant();
            if (this_plant == nullptr)
            {
                currentPlants[i][j] = 0;
            }
            else
            {
                currentPlants[i][j] = this_plant->getPlant_Type();
            }
        }
    }
    return currentPlants;
}

int*** Camp::getCurrentZombies()
{
    int rows = Field->GetRows(), columns = Field->GetColumns();
    grid** NowGrid = Field->grids;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            delete[] currentZombies[i][j];
            vector<int>nowZombie = NowGrid[i][j].GetThisGridZombie();
            currentZombies[i][j] = new int[nowZombie.size() + 1];
            currentZombies[i][j][nowZombie.size()] = -1;
            for (int k = 0; k < nowZombie.size(); k++)
            {
                currentZombies[i][j][k] = Field->allZombies[nowZombie[k]]->getZombie_Type();
            }
        }
    }
    return currentZombies;
}

int* Camp::getLeftLines()
{
    int rows = Field->GetRows();
    grid** NowGrid = Field->grids;
    for (int i = 0; i < rows; i++)
    {
        leftLines[i] = Field->FallRecord[i];
        
    }
    return leftLines;
}

void Camp::setSun(int _sun)
{
    sun = _sun;
}

void Camp::addSun(int _sun)
{
    sun += _sun;
}

Camp::~Camp()
{
    int rows = Field->GetRows(), columns = Field->GetColumns();
    delete[] leftLines;
    for(int i = 0; i < rows; i++)
    {
        delete[] currentPlants[i];
        for(int j = 0; j < rows; j++)
        {
            delete[] currentZombies[i][j];
        }
        delete[] currentZombies[i];
    }
    delete[] currentPlants;
    delete[] currentZombies;
}
PlantCamp::PlantCamp(field* _field, int _sun):Camp(_field, _sun)
{
    LastPlacePlant.resize(6, -1000);
    PlantCD = {10, 30, 10, 40, 60, 60};
    NowCD = new int[6];
    for (int i = 0; i < 6; i++)
    {
        NowCD[i] = 0;
    }
}

bool PlantCamp::PlacePlant(int x, int y, int type)
{
    if (Field->FallRecord[x] == 0)
        return false;
    plants* plant;
    bool IsPlaced;
    int* CD = getPlantCD();
    switch (type)
    {
    case (int)SUNFLOWER:

        plant = new Sunflower(Game::getTime(), x, y, Game::index);
        if (CD[0] != 0 || sun < plant->getSun())
            IsPlaced = false;
        else {
            IsPlaced = Field->PlacePlant(x, y, plant);
        }
        if (!IsPlaced)
            delete plant;
        else {
            Game::index++;
            sun -= plant->getSun();
            LastPlacePlant[type - 1] = Game::getTime();
        }
        break;
    case (int)WINTERPEASHOOTER:
        plant = new WinterPeaShooter(Game::getTime(), x, y, Game::index);
        if (CD[1] != 0 || sun < plant->getSun())
            IsPlaced = false;
        else {
            IsPlaced = Field->PlacePlant(x, y, plant);
        }
        if (!IsPlaced)
            delete plant;
        else {
            Game::index++;
            sun -= plant->getSun();
            LastPlacePlant[type - 1] = Game::getTime();
        }
        break;
    case (int)PEASHOOTER:
        plant = new PeaShooter(Game::getTime(), x, y, Game::index);
        if (CD[2] != 0 || sun < plant->getSun())
            IsPlaced = false;
        else {
            IsPlaced = Field->PlacePlant(x, y, plant);
        }
        if (!IsPlaced)
            delete plant;
        else {
            Game::index++;
            sun -= plant->getSun();
            LastPlacePlant[type - 1] = Game::getTime();
        }
        break;
    case (int)SMALLNUT:
        plant = new SmallNut(Game::getTime(), x, y, Game::index);
        if (CD[3]!=0 || sun < plant->getSun())
            IsPlaced = false;
        else {
            IsPlaced = Field->PlacePlant(x, y, plant);
        }
        if (!IsPlaced)
            delete plant;
        else {
            Game::index++;
            sun -= plant->getSun();
            LastPlacePlant[type - 1] = Game::getTime();
        }
        break;
    case (int)PEPPER:
        plant = new Pepper(Game::getTime(), x, y, Game::index);
        if (CD[4]!=0 || sun < plant->getSun())
            IsPlaced = false;
        else {
            IsPlaced = Field->PlacePlant(x, y, plant);
        }
        if (!IsPlaced)
            delete plant;
        else {
            Game::index++;
            sun -= plant->getSun();
            LastPlacePlant[type - 1] = Game::getTime();
        }
        break;
    case (int)SQUASH:
        plant = new Squash(Game::getTime(), x, y, Game::index);
        if (CD[5] != 0 || sun < plant->getSun())
            IsPlaced = false;
        else {
            IsPlaced = Field->PlacePlant(x, y, plant);
        }
        if (!IsPlaced)
            delete plant;
        else {
            Game::index++;
            sun -= plant->getSun();
            LastPlacePlant[type - 1] = Game::getTime();
        }
        break;
    default:
        IsPlaced = false;
        break;
    }

    return IsPlaced;
}
bool PlantCamp::RemovePlant(int x, int y)
{
    return Field->RemovePlant(x, y);
}

bool ZombieCamp::PlaceZombie(int y, int type)
{
    if (Field->FallRecord[y] == 0)
        return false;
    zombies* zombie = nullptr;
    int* CD = getPlantCD();
    bool IsPlaced;
    switch (type)
    {
    case (int)NORMAL:
        zombie = new NormalZombies(Game::getTime(), y, Game::index);
        if (CD[0] != 0 || sun < zombie->getSun()) {
            IsPlaced = false;
        }
        else {
            IsPlaced = Field->PlaceZombie(y, zombie);
        }
        if (!IsPlaced)
            delete zombie;
        else {
            Game::index++;
            sun -= zombie->getSun();
            LastPlaceZombie[type - 1] = Game::getTime();
        }
        break;
    case (int)BUCKET:
        zombie = new BucketZombies(Game::getTime(), y, Game::index);
        if (CD[1] != 0 || sun < zombie->getSun()) {
            IsPlaced = false;
        }
        else {
            IsPlaced = Field->PlaceZombie(y, zombie);
        }
        if (!IsPlaced)
            delete zombie;
        else {
            Game::index++;
            sun -= zombie->getSun();
            LastPlaceZombie[type - 1] = Game::getTime();
        }
        break;
    case (int)POLEVAULT:
        zombie = new PolevaultZombies(Game::getTime(), y, Game::index);
        if (CD[2] != 0 || sun < zombie->getSun()) {
            IsPlaced = false;
        }
        else {
            IsPlaced = Field->PlaceZombie(y, zombie);
        }
        if (!IsPlaced)
            delete zombie;
        else {
            Game::index++;
            sun -= zombie->getSun();
            LastPlaceZombie[type - 1] = Game::getTime();
        }
        break;
    case (int)SLED:
        zombie = new SledZombies(Game::getTime(), y, Game::index);
        if (CD[3] != 0 || sun < zombie->getSun()) {
            IsPlaced = false;
        }
        else {
            IsPlaced = Field->PlaceZombie(y, zombie);
        }
        if (!IsPlaced)
            delete zombie;
        else {
            Game::index++;
            sun -= zombie->getSun();
            LastPlaceZombie[type - 1] = Game::getTime();
        }
        break;
    case (int)GARGANTUAR:
        zombie = new gargantuar(Game::getTime(), y, Game::index);
        if (CD[4] != 0 || sun < zombie->getSun()) {
            IsPlaced = false;
        }
        else {
            IsPlaced = Field->PlaceZombie(y, zombie);
        }
        if (!IsPlaced)
            delete zombie;
        else {
            Game::index++;
            sun -= zombie->getSun();
            LastPlaceZombie[type - 1] = Game::getTime();
        }
        break;
    default:
        IsPlaced = false;
        break;
    }
    return IsPlaced;
}

int* PlantCamp::getPlantCD()
{
    for (int i = 0; i < 6; i++) {
        NowCD[i] = LastPlacePlant[i] + PlantCD[i] - Game::getTime();
        if (NowCD[i] < 0)
            NowCD[i] = 0;
    }
    return NowCD;
}

int* ZombieCamp::getPlantCD()
{
    for (int i = 0; i < 5; i++) {
        NowCD[i] = LastPlaceZombie[i] + PlantCD[i] - Game::getTime();
        if (NowCD[i] < 0)
            NowCD[i] = 0;
    }
    return NowCD;
}

ZombieCamp::ZombieCamp(field* _field, int _sun):Camp(_field, _sun)
{
    LastPlaceZombie.resize(5, -1000);
    int time = Game::getTime();
    PlantCD = {15, 20, 20, 25, 25};
    NowCD = new int[5];
    for(int i = 0; i < 5; i++)
    {
        NowCD[i] = 0;
    }
}
