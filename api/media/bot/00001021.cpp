#include "ai.h"
//选手代码在下方填入
int leastplants(int** A)
{
	int* B;
	B = new int[5];
	for (int i = 0; i < 5; i++) {
		B[i] = 0;
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 9; j++) {
			if (A[i][j] != 0)B[i]++;
		}
	}
	int k = 0;
	for (int i = 0; i < 5; i++)
	{
		if (B[i] <= B[k])k = i;
	}
	return k;
}
int nextCurrentrow(int* A, int row)
{
	int m;
	for (m = row + 1; m < 5; m++)
	{
		if (A[row] == 0)row++;
		else {
			return row;
		}
		if (m == 5)return -1;
	}
}
void player_ai(IPlayer* player) {
	int Type = player->Camp->getCurrentType();
	if (Type == 0) {
		int m = 6;
		int n = 0;
		int pp = 0;
		int kk = 0;
		bool warning = false;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				int*** p = player->Camp->getCurrentZombies();
				int k = 0;
				while (p[i][j][k] != -1)
				{
					if (j == 1)
					{
						player->PlacePlant(5, i, j);
						player->PlacePlant(6, i, j - 1);
					}
					else if (p[i][j][k] >= 4 && j >= 2)
					{
						player->PlacePlant(5, i, j);
						player->PlacePlant(6, i, j - 1);
					}
					else
					{
						player->PlacePlant(4, i, j);
						player->PlacePlant(2, i, j - 1);
					}
					k++;
				}
				pp += k;
			}
			if (pp > n)
			{
				n = pp; m = i;
			}
			pp = 0;
		}
		for (int i = 0; i < 5; i++)
			player->PlacePlant(1, i, 0);
		for (int i = 0; i < 5; i++)
		{
			player->PlacePlant(6, 5 - i, 5);
			player->PlacePlant(6, i, 4);
			player->PlacePlant(6, i * 2 / 3 + 2, 5);
			player->PlacePlant(6, i * 3 / 4, 4);
		}
		if (player->Camp->getSun() > 175)
			for (int i = 0; i < 5; i++)
				player->PlacePlant(1, i, 1);
		if (player->Camp->getSun() > 300)
			for (int i = 0; i < 5; i++)
			{
				player->PlacePlant(2, i, 2);
				player->PlacePlant(6, i, 3);
				player->PlacePlant(4, 5 - i, 8);
			}
		if(player->getTime()>=500)
		for (int i = 0; i < 5; i++)
		{
			player->PlacePlant(6, 5 - i, 1);
			player->PlacePlant(2, i, 3);
			player->PlacePlant(4, i, 7);
		}
		
	}
		
		/*if (Type == 1)
		{
			int BrokenLinesScore = player->getBrokenLinesScore();
			int KillPlantsScore = player->getKillPlantsScore();
			int Score = player->getScore();
			int time = player->getTime();
			int rows = player->Camp->getRows();
			int columns = player->Camp->getColumns();
			int* PlantCD = player->Camp->getPlantCD();
			int** Plants = player->Camp->getCurrentPlants();
			int*** Zombies = player->Camp->getCurrentZombies();
			int Sun = player->Camp->getSun();
			int* LeftLines = player->Camp->getLeftLines();
			//
			//
			//
			int i = 0, j = 0;
			int rowplants[5] = { 0 };
			if (time == 1)player->PlaceZombie(1, 2);
			if (time == 2)player->PlaceZombie(2, 4);
			if (time == 10)player->PlaceZombie(3, 4);
			if (time >= 200 && time <= 300)
			{
				if (Sun >= 300) {
					if (time == 250) {
						player->PlaceZombie(1, 1);
						player->PlaceZombie(2, 3);
						player->PlaceZombie(3, 3);
					}
				}
				if (Sun < 300) {
					if (PlantCD[1] != 0 && Sun > 150)player->PlaceZombie(1, 5);
					if (PlantCD[5] != 0 && Sun > 200)player->PlaceZombie(3, 5);
				}
			}
			if (time == 485)
			{
				player->PlaceZombie(5, leastplants(Plants));
			}
			if (time == 499)
			{
				for (i = 0; i < 5; i++) {
					if (LeftLines[i] != 0)player->PlaceZombie(1, i);
					break;
				}
			}
			if (time == 501) {
				if (Sun >= 350)
					for (i++; i < 5; i++)
					{
						if (LeftLines[i] != 0)
						{
							player->PlaceZombie(1, i);
						}
					}
			}
			if (time == 505) {
				player->PlaceZombie(5, i);
				int p = nextCurrentrow(LeftLines, i);
				if (Sun >= 300 && p != -1)
					player->PlaceZombie(4, p);
				if (Sun >= 450 && nextCurrentrow(LeftLines, p) != -1)
					player->PlaceZombie(2, nextCurrentrow(LeftLines, p));
			}
			if (time == 550)
			{
				if (Sun > 500)
				{
					player->PlaceZombie(5, nextCurrentrow(LeftLines, 0));
					player->PlaceZombie(4, nextCurrentrow(LeftLines, nextCurrentrow(LeftLines, 0)));
				}
			}
			if (time == 999)
			{
				player->PlaceZombie(1, leastplants(Plants));
				if (Sun >= 450)player->PlaceZombie(5, nextCurrentrow(LeftLines, 0));
			}
			if (time == 1000)
			{
				player->PlaceZombie(1, leastplants(Plants));
			}
			if (time == 1005)
			{
				player->PlaceZombie(5, nextCurrentrow(LeftLines, 0));
			}
			if (time == 1100)
			{
				if (Sun > 500)
				{
					player->PlaceZombie(5, nextCurrentrow(LeftLines, 0));
					player->PlaceZombie(4, nextCurrentrow(LeftLines, nextCurrentrow(LeftLines, 0)));
				}
			}
			if (time == 1499)
			{
				player->PlaceZombie(1, nextCurrentrow(LeftLines, nextCurrentrow(LeftLines, 0)));
				player->PlaceZombie(5, nextCurrentrow(LeftLines, 0));
			}
			if (time >= 1500 && time < 1700)
			{
				if (Sun > 450)
				{
					if (PlantCD[5] == 0)player->PlaceZombie(5, nextCurrentrow(LeftLines, 0));
					if (PlantCD[3] == 0)player->PlaceZombie(3, nextCurrentrow(LeftLines, 0));
				}
			}
			if (time >= 1700 && time <= 1900)
			{
				if (Sun > 300 && PlantCD[5] == 0)player->PlaceZombie(5, nextCurrentrow(LeftLines, 0));
				if (Sun > 300 && PlantCD[2] == 0)player->PlaceZombie(2, nextCurrentrow(LeftLines, 0));
			}
			if (time >= 1800 && time < 2000)
			{
				if (Sun > 300 && PlantCD[5] == 0)player->PlaceZombie(5, nextCurrentrow(LeftLines, 0));
				if (Sun > 300 && PlantCD[4] == 0)player->PlaceZombie(4, nextCurrentrow(LeftLines, 0));
			}

		}*/
    }
