#include "ai.h"
#include<iostream>
extern"C" _declspec(dllexport) void player_ai(IPlayer * player)
{
	int time = player->getTime();//��õ�ǰ�غ���
	int rows = player->Camp->getRows();//�������
	int columns = player->Camp->getColumns();//�������
	int type = player->Camp->getCurrentType();//��õ�ǰ�������
	int** plants = player->Camp->getCurrentPlants();//��ǰֲ�������ά����
	int*** zombies = player->Camp->getCurrentZombies();//��ǰ��ʬ�����ά����

	//���������˺ܶ��һά���飬���Լ���ĳһ��ÿ��ֲ���ʬ����������Ѱ���ĳһ�е����Ž�
	int rowPlantNum[5] = { 0,0,0,0,0 };//ֲ������
	int rowZombieNum[5] = { 0,0,0,0,0 };//��ʬ����
	int rowPeaNum[5] = { 0,0,0,0,0 };//�㶹��������
	int rowIceNum[5] = { 0,0,0,0,0 };//���㶹��������
	int rowPumpkinNum[5] = { 0,0,0,0,0 };//��������
	int rowNutNum[5] = { 0,0,0,0,0 };//�������

	//����ֲ���ά�������ÿ��ֲ�������Ӧ������
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
	//������ʬ��ά�������ÿ�н�ʬ�����Ӧ������
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
	
	//ֲ�﷽����
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
	//��ʬ������
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