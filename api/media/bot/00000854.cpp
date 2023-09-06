#include "ai.h"
#include<iostream>
extern"C" _declspec(dllexport) void player_ai(IPlayer * player)
{
	int time = player->getTime();//获得当前回合数
	int rows = player->Camp->getRows();//获得行数
	int columns = player->Camp->getColumns();//获得列数
	int type = player->Camp->getCurrentType();//获得当前玩家类型
	int** plants = player->Camp->getCurrentPlants();//当前植物情况二维数组
	int*** zombies = player->Camp->getCurrentZombies();//当前僵尸情况三维数组

	//以下声明了很多个一维数组，用以计算某一行每种植物或僵尸数量，进而寻求对某一行的最优解
	int rowPlantNum[5] = { 0,0,0,0,0 };//植物总数
	int rowZombieNum[5] = { 0,0,0,0,0 };//僵尸总数
	int rowPeaNum[5] = { 0,0,0,0,0 };//豌豆射手总数
	int rowIceNum[5] = { 0,0,0,0,0 };//冰豌豆射手总数
	int rowPumpkinNum[5] = { 0,0,0,0,0 };//倭瓜总数
	int rowNutNum[5] = { 0,0,0,0,0 };//坚果总数

	//遍历植物二维数组计算每行植物数组对应的数量
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (plants[i][j] != 0)
			{
				rowPlantNum[i] += 1;
			}
			if (plants[i][j] == 2)
			{
				rowIceNum[i] += 1;
			}
			if (plants[i][j] == 3)
			{
				rowPeaNum[i] += 1;
			}
			if (plants[i][j] == 5)
			{
				rowPumpkinNum[i] += 1;
			}
			if (plants[i][j] == 6)
			{
				rowNutNum[i] += 1;
			}
		}
	}
	//遍历僵尸三维数组计算每行僵尸数组对应的数量
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			int k = 0;
			while (zombies[i][j][k] != -1)
			{
				rowZombieNum[i] += 1;
				k++;
			}
		}
	}
	
	//植物方策略
	if (type == 0)
	{
		int* plantCD = player->Camp->getPlantCD();
		if (plantCD[3] == 0)
		{
			player->PlacePlant(3, 0, 0);
		}
		if (plantCD[1] == 0)
		{
			player->PlacePlant(1, 1, 0);
		}
	}
	//僵尸方策略
	if (type == 1)
	{
		int sun = player->Camp->getSun();
		int* zombieCD = player->Camp->getPlantCD();

		for (int i = 0; i < rows; i++)
		{
			if (rowPeaNum[i] != 0 || rowIceNum[i] != 0)
			{
				if (rowPumpkinNum[i] == 0)
				{
					if (rowNutNum[i] == 0)
					{
						if (rowIceNum[i] == 0)
						{
							if (rowZombieNum[i] == 0)
							{
								if (zombieCD[2] == 0)
								{
									player->PlaceZombie(2, i);
								}
							}
						}
						else
						{
							if (rowZombieNum[i] <= 1)
							{
								player->PlaceZombie(4, i);
							}
						}
					}
				}
			}

			else if(time != 1)
			{
				if (rowPumpkinNum[i] == 0)
				{
					if (rowZombieNum[i] == 0)
					{
						player->PlaceZombie(1, i);
					}
				}		
			}
		}			
	}
}