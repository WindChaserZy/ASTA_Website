#include "ai.h"
//选手代码在下方填入
#include <iostream>
#include <math.h>
int Zombies[5][10][10] = { -1 };//前一回合僵尸信息
int Plants[5][10] = { 0 };//前一回合植物信息
int ZombiesAccurate[5][10][3] = { 0 };//现在的僵尸精确信息（Zombies[i][j][0]~[2]分别是第i行第j个（不按顺序）僵尸的类型、血量与速度）
int NutBlood[5][10] = { 0 };//场上坚果的血量
static int ***Zombies;
static int **Plants;
static int KillZombieScore = 0;
static int Moon = 300;
static int WholeMoon = 0;
void player_ai(IPlayer *player)
{
    int Type = player->Camp->getCurrentType();
    if (Type == 0)
    {
        const int ZombiesBlood[6] = {0, 270 * 3, 820 * 3, 200 * 3, 1600 * 3, 3000 * 3}; //僵尸血量，因为豌豆的攻击力是20 / 3，所以我将僵尸血量与豌豆的攻击力都乘上3
        const int ZombiesSpeed[7] = {0, 2, 2, 4, 2, 2, 2};                              //僵尸速度，ZombiesSpeeed[6]为撑杆跳僵尸跳完的速度，我还没有求得雪橇车的精确速度
        int Giant[5] = {0};                                                             //如果第i行有巨人，那么等于1
        int Sled[5] = {0};
        int *LeftLines = player->Camp->getLeftLines();
        int ***ZombiesNow = player->Camp->getCurrentZombies(); //当前回合僵尸信息
        int **PlantsNow = player->Camp->getCurrentPlants();    //当前回合植物信息
        int Nearest[5] = {-1, -1, -1, -1, -1};                 //最近的僵尸编号，初始值为-1
        int *PlantCD = player->Camp->getPlantCD();             //植物CD
        int Sun = player->Camp->getSun();                      //阳光
        //统计豌豆的数量
        int SunflowerNum[5] = {0};
        int PeashooterNum[5][2] = {0};    // PeashootNum[i][0]为豌豆数量，[1]为冰豌豆数量
        int HasWinterPeashooter[5] = {0}; //如果一行中有冰豌豆，那么为1，在后续计算中，如果为1那么最前方僵尸速度减半
        for (int i = 0; i < 5; i++)
        {
            if (LeftLines[i] == 0)
            {
                continue;
            }
            for (int j = 0; j < 10; j++)
            {
                if (PlantsNow[i][j] == 3)
                {
                    PeashooterNum[i][0]++;
                }
                if (PlantsNow[i][j] == 2)
                {
                    PeashooterNum[i][1]++;
                    HasWinterPeashooter[i] = 1;
                }
                if (PlantsNow[i][j] == 1)
                {
                    SunflowerNum[i]++;
                }
            }
        }
        //统计僵尸的血量、位置和类型
        for (int i = 0; i < 5; i++)
        {
            if (LeftLines[i] == 0)
            {
                continue;
            }
            for (int k = 0; ZombiesNow[i][9][k] != -1; k++)
            {
                int HasSameZombie = 0; //如果上一回合与这一回合的最右方的格子内有相同类型的僵尸，则视作他们是同一个僵尸，如果这一回合有而上一回合没有，那么视作僵尸方放置了一个新的僵尸
                for (int m = 0; Zombies[i][9][m] != -1; m++)
                {
                    if (ZombiesNow[i][9][k] == Zombies[i][9][m])
                    {
                        HasSameZombie = 1;
                        break;
                    }
                }
                if (HasSameZombie == 0)
                {
                    int m = 0;
                    for (; ZombiesAccurate[i][m][0] != 0;)
                    {
                        m++;
                    }
                    ZombiesAccurate[i][m][0] = ZombiesNow[i][9][k];               //僵尸类型
                    ZombiesAccurate[i][m][1] = ZombiesBlood[ZombiesNow[i][9][k]]; //僵尸血量
                    ZombiesAccurate[i][m][2] = 100;                               //僵尸位置，为方便存储，此处乘上了10
                }
            }
        }
        //计算一行中有无雪橇车或巨人
        for (int i = 0; i < 5; i++)
        {
            if (LeftLines[i] == 0)
            {
                continue;
            }
            for (int j = 0; j < 10; j++)
            {
                for (int k = 0; ZombiesNow[i][j][k] != -1; k++)
                {
                    if (ZombiesNow[i][j][k] == 4)
                    {
                        Sled[i] = 1;
                    }
                    if (ZombiesNow[i][j][k] == 5)
                    {
                        Giant[i] = 1;
                    }
                }
            }
        }
        //如果僵尸死亡，将它的信息抹除，如果僵尸到达终点，将一行的信息都抹除
        for (int i = 0; i < 5; i++)
        {
            if (LeftLines[i] == 0)
            {
                continue;
            }
            for (int j = 0; j < 10; j++)
            {
                if (ZombiesAccurate[i][j][0] == 0)
                {
                    continue;
                }
                if (ZombiesAccurate[i][j][2] <= 0)
                {
                    for (int k = 0; k < 10; k++)
                    {
                        for (int n = 0; n < 3; n++)
                        {
                            ZombiesAccurate[i][k][n] = 0;
                        }
                    }
                    break;
                }
                if (ZombiesAccurate[i][j][1] <= 0)
                {
                    ZombiesAccurate[i][j][0] = 0;
                    ZombiesAccurate[i][j][1] = 0;
                    ZombiesAccurate[i][j][2] = 0;
                    continue;
                }
            }
        }
        //计算推进最快的僵尸的编号
        for (int i = 0; i < 5; i++)
        {
            if (LeftLines[i] == 0)
            {
                continue;
            }
            for (int j = 0; j < 10; j++)
            {
                if (ZombiesAccurate[i][j][0] != 0)
                {
                    if (Nearest[i] == -1)
                    {
                        Nearest[i] = j;
                    }
                    else
                    {
                        if (ZombiesAccurate[i][j][2] < ZombiesAccurate[i][Nearest[i]][2])
                        {
                            Nearest[i] = j;
                        }
                    }
                }
            }
        }
        //计算每回合僵尸的扣血
        for (int i = 0; i < 5; i++)
        {
            if (LeftLines[i] == 0)
            {
                continue;
            }
            if (Nearest[i] != -1)
            {
                ZombiesAccurate[i][Nearest[i]][1] -= PeashooterNum[i][0] * 20; //最前方僵尸受到豌豆的伤害
                for (int j = 0; j < 10; j++)
                {
                    if (ZombiesAccurate[i][j][2] == ZombiesAccurate[i][Nearest[i]][2])
                    {
                        ZombiesAccurate[i][j][1] -= PeashooterNum[i][1] * 45; //最前方僵尸所处格内的所有僵尸受到冰豌豆的伤害
                    }
                }
            }
        }
        //计算僵尸位置
        for (int i = 0; i < 5; i++)
        {
            if (LeftLines[i] == 0)
            {
                continue;
            }
            for (int j = 0; j < 10; j++)
            {
                if (ZombiesAccurate[i][j][0] != 3 && ZombiesAccurate[i][j][0] != 4)
                {
                    if ((ZombiesAccurate[i][j][0] != 0 && PlantsNow[i][ZombiesAccurate[i][j][2] / 10] == 0) || ZombiesAccurate[i][j][2] == 100)
                    {
                        ZombiesAccurate[i][j][2] -= ZombiesSpeed[ZombiesAccurate[i][j][0]];
                        if (Nearest[i] != -1 && ZombiesAccurate[i][j][2] == ZombiesAccurate[i][Nearest[i]][2] && HasWinterPeashooter[i] == 1)
                        {
                            ZombiesAccurate[i][j][2] += 1 / 2 * ZombiesSpeed[ZombiesAccurate[i][j][0]];
                        }
                    }
                }
                if (ZombiesAccurate[i][j][0] == 3 && ZombiesAccurate[i][j][2] > 7) //如果是撑杆跳僵尸
                {
                    ZombiesAccurate[i][j][2] -= ZombiesSpeed[ZombiesAccurate[i][j][0]];
                }
                else if (ZombiesAccurate[i][j][0] == 3 && ZombiesAccurate[i][j][2] == 7)
                {
                    ZombiesAccurate[i][j][2] -= 10;
                }
                else if (ZombiesAccurate[i][j][0] == 3 && ZombiesAccurate[i][j][2] < 6 && PlantsNow[i][6] > 0)
                {
                    ZombiesAccurate[i][j][0] = 6;
                    ZombiesAccurate[i][j][2] -= ZombiesSpeed[ZombiesAccurate[i][j][0]];
                }
                else if (ZombiesAccurate[i][j][0] == 3 && ZombiesAccurate[i][j][2] <= 6 && PlantsNow[i][6] == 0)
                {
                    ZombiesAccurate[i][j][2] -= ZombiesSpeed[ZombiesAccurate[i][j][0]];
                }
                if (ZombiesAccurate[i][j][0] == 4)
                {
                    //此处未想好如何计算雪橇车的速度
                }
            }
        }
        //以上计算出了僵尸的精确信息，且已确认无误，问题都出现在下方
        //决策植物
        int NearestPlant[5] = {-1, -1, -1, -1, -1}; //最右端的植物位置（不包括坚果、倭瓜和辣椒）
        int CanResolve[5] = {0};                    //如果这一行的问题可以解决，那么为1
        int NutDelay[5] = {0, 0, 0, 0, 0};          //存储坚果可以延缓的秒数
        for (int i = 0; i < 5; i++)
        {
            if (LeftLines[i] == 0)
            {
                continue;
            }
            for (int j = 0; j < 10; j++)
            {
                if (PlantsNow[i][j] - Plants[i][j] == 4) //有新坚果
                {
                    NutBlood[i][j] = 4000;
                }
            }
        }
        //计算坚果的扣血
        for (int i = 0; i < 5; i++)
        {
            if (LeftLines[i] == 0)
            {
                continue;
            }
            int ZombieNum = 0; //与坚果在同一格的僵尸数量
            for (int k = 0; ZombiesNow[i][6][k] != -1; k++)
            {
                if (ZombiesNow[i][6][k] == 4 || ZombiesNow[i][6][k] == 5) //如果有巨人和雪橇车，那么坚果被秒杀
                {
                    NutBlood[i][6] = 0;
                    NutDelay[i] = 0;
                    break;
                }
                else
                {
                    NutBlood[i][6] -= 75;
                    ZombieNum++;
                }
            }
            if (NutBlood[i][6] <= 0)
            {
                NutBlood[i][6] = 0;
            }
            if (ZombieNum != 0)
            {
                NutDelay[i] = NutBlood[i][6] / (ZombieNum * 75); //坚果能延缓的秒数是坚果血量除以僵尸总攻击力
            }
        }
        //下面计算最右端的植物位置
        for (int i = 0; i < 5; i++)
        {
            if (LeftLines[i] == 0)
            {
                continue;
            }
            for (int j = 0; j < 10; j++)
            {
                if (PlantsNow[i][j] && j > NearestPlant[i] && PlantsNow[i][j] != 4 && PlantsNow[i][j] != 5 && PlantsNow[i][j] != 6)
                {
                    NearestPlant[i] = j;
                }
            }
        }
        //下面判断一行能否守住
        for (int i = 0; i < 5; i++)
        {
            if (LeftLines[i] == 0)
            {
                continue;
            }
            if (ZombiesAccurate[i][Nearest[i]][0] != 0) //如果有僵尸
            {
                int TimeToKill = -NutDelay[i];                            //杀死僵尸需要花的时间，坚果会减少这一时间，甚至让它变成负的
                int BloodToDamage = ZombiesAccurate[i][Nearest[i]][1];    //需要造成的伤害
                int DistanceToWait = ZombiesAccurate[i][Nearest[i]][2];   //僵尸将在这段时间内前进的距离
                if (PeashooterNum[i][0] != 0 || PeashooterNum[i][1] != 0) //如果这一行有豌豆
                {
                    for (; BloodToDamage > 0; TimeToKill++)
                    {
                        BloodToDamage -= PeashooterNum[i][0] * 20;
                        BloodToDamage -= PeashooterNum[i][1] * 45;
                    }
                    DistanceToWait -= ZombiesSpeed[ZombiesAccurate[i][Nearest[i]][0]] * TimeToKill;
                    if (HasWinterPeashooter[i] == 1)
                    {
                        DistanceToWait += 1 / 2 * ZombiesSpeed[ZombiesAccurate[i][Nearest[i]][0]] * TimeToKill;
                    }
                }
                else
                {
                    DistanceToWait = 0; //这一行没有豌豆，那么僵尸将无休止的前进
                }
                if (DistanceToWait - 10 * NearestPlant[i] < 5 || NearestPlant[i] == -1) //如果这一行根本没有植物或者僵尸与植物间距离将达到很小（距离为0.5格）时
                {
                    if (PeashooterNum[i][0] == 0 && PeashooterNum[i][1] == 0 && ZombiesAccurate[i][Nearest[i]][0] != 4 && ZombiesAccurate[i][Nearest[i]][0] != 5 && PlantCD[2] == 0 && Sun >= 100) //如果这一行还没有豌豆并且僵尸不是雪橇车或者巨人并且可以种豌豆的话，那就种豌豆
                    {
                        player->PlacePlant(3, i, NearestPlant[i] + 1);
                        PeashooterNum[i][0]++;
                        NearestPlant[i]++;
                        PlantCD[2] = 10;
                        Sun -= 100;
                        //下面检验问题是否解决（也就是再进行一次上面的判断）
                        TimeToKill = -NutDelay[i];
                        BloodToDamage = ZombiesAccurate[i][Nearest[i]][1];
                        DistanceToWait = ZombiesAccurate[i][Nearest[i]][2];
                        if (PeashooterNum[i][0] != 0 || PeashooterNum[i][1] != 0)
                        {
                            for (; BloodToDamage > 0; TimeToKill++)
                            {
                                BloodToDamage -= PeashooterNum[i][0] * 20;
                                BloodToDamage -= PeashooterNum[i][1] * 45;
                            }
                            DistanceToWait -= ZombiesSpeed[ZombiesAccurate[i][Nearest[i]][0]] * TimeToKill;
                            if (HasWinterPeashooter[i] == 1)
                            {
                                DistanceToWait += 1 / 2 * ZombiesSpeed[ZombiesAccurate[i][Nearest[i]][0]] * TimeToKill;
                            }
                        }
                        else
                        {
                            DistanceToWait = 0;
                        }
                        if (DistanceToWait - 10 * NearestPlant[i] > 5) //如果解决了
                        {
                            CanResolve[i] = 1;
                            continue; //不用进行后续的判断了，直接跳到下一行
                        }
                    }
                    if (PlantCD[2] != 0 || Sun < 100) //如果种不了豌豆，看看能不能种冰豌豆
                    {
                        if (Sun >= 400 && PlantCD[1] == 0)
                        {
                            player->PlacePlant(2, i, NearestPlant[i] + 1);
                            PeashooterNum[i][1]++;
                            NearestPlant[i]++;
                            PlantCD[1] = 30;
                            Sun -= 400;
                            TimeToKill = -NutDelay[i];
                            BloodToDamage = ZombiesAccurate[i][Nearest[i]][1];
                            DistanceToWait = ZombiesAccurate[i][Nearest[i]][2];
                            if (PeashooterNum[i][0] != 0 || PeashooterNum[i][1] != 0)
                            {
                                for (; BloodToDamage > 0; TimeToKill++)
                                {
                                    BloodToDamage -= PeashooterNum[i][0] * 20;
                                    BloodToDamage -= PeashooterNum[i][1] * 45;
                                }
                                DistanceToWait -= ZombiesSpeed[ZombiesAccurate[i][Nearest[i]][0]] * TimeToKill;
                                if (HasWinterPeashooter[i] == 1)
                                {
                                    DistanceToWait += 1 / 2 * ZombiesSpeed[ZombiesAccurate[i][Nearest[i]][0]] * TimeToKill;
                                }
                            }
                            else
                            {
                                DistanceToWait = 0;
                            }
                            if (DistanceToWait - 10 * NearestPlant[i] > 5)
                            {
                                CanResolve[i] = 1;
                                continue;
                            }
                        }
                    }
                    if (Sled[i] == 0 && Giant[i] == 0) //如果没有巨人或者雪橇车，看看种豌豆能不能解决
                    {
                        if (PlantCD[2] == 0 && Sun >= 100 && PeashooterNum[i][0] <= 1)
                        {
                            player->PlacePlant(3, i, NearestPlant[i] + 1);
                            PeashooterNum[i][0]++;
                            NearestPlant[i]++;
                            Sun -= 100;
                            PlantCD[2] = 10;
                            TimeToKill = -NutDelay[i];
                            BloodToDamage = ZombiesAccurate[i][Nearest[i]][1];
                            DistanceToWait = ZombiesAccurate[i][Nearest[i]][2];
                            if (PeashooterNum[i][0] != 0 || PeashooterNum[i][1] != 0)
                            {
                                for (; BloodToDamage > 0; TimeToKill++)
                                {
                                    BloodToDamage -= PeashooterNum[i][0] * 20;
                                    BloodToDamage -= PeashooterNum[i][1] * 45;
                                }
                                DistanceToWait -= ZombiesSpeed[ZombiesAccurate[i][Nearest[i]][0]] * TimeToKill;
                                if (HasWinterPeashooter[i] == 1)
                                {
                                    DistanceToWait += 1 / 2 * ZombiesSpeed[ZombiesAccurate[i][Nearest[i]][0]] * TimeToKill;
                                }
                            }
                            else
                            {
                                DistanceToWait = 0;
                            }
                            if (DistanceToWait - 10 * NearestPlant[i] > 5)
                            {
                                CanResolve[i] = 1;
                                continue;
                            }
                        }
                        if (PlantCD[1] == 0 && Sun >= 400 && PeashooterNum[i][1] <= 1)
                        {
                            player->PlacePlant(3, i, NearestPlant[i] + 1);
                            PeashooterNum[i][0]++;
                            NearestPlant[i]++;
                            PlantCD[1] = 30;
                            Sun -= 100;
                            TimeToKill = -NutDelay[i];
                            BloodToDamage = ZombiesAccurate[i][Nearest[i]][1];
                            DistanceToWait = ZombiesAccurate[i][Nearest[i]][2];
                            if (PeashooterNum[i][0] != 0 || PeashooterNum[i][1] != 0)
                            {
                                for (; BloodToDamage > 0; TimeToKill++)
                                {
                                    BloodToDamage -= PeashooterNum[i][0] * 20;
                                    BloodToDamage -= PeashooterNum[i][1] * 45;
                                }
                                DistanceToWait -= ZombiesSpeed[ZombiesAccurate[i][Nearest[i]][0]] * TimeToKill;
                                if (HasWinterPeashooter[i] == 1)
                                {
                                    DistanceToWait += 1 / 2 * ZombiesSpeed[ZombiesAccurate[i][Nearest[i]][0]] * TimeToKill;
                                }
                            }
                            else
                            {
                                DistanceToWait = 0;
                            }
                            if (DistanceToWait - 10 * NearestPlant[i] > 5)
                            {
                                CanResolve[i] = 1;
                                continue;
                            }
                        }
                    }
                    if (ZombiesAccurate[i][Nearest[i]][2] > 60 && Sled[i] == 0 && Giant[i] == 0 && PlantCD[3] == 0 && Sun >= 50 && PlantsNow[i][6] == 0) //如果还没解决，并且僵尸在第六格之前，并且僵尸不是雪橇车或者巨人，并且能种坚果，那就在第六格种坚果
                    {
                        player->PlacePlant(4, i, 6);
                        Sun -= 50;
                        PlantCD[3] = 40;
                        NutBlood[i][6] = 4000;
                        CanResolve[i] = 1; //由于不管是普通僵尸还是撑杆跳还是铁桶僵尸都无法活过坚果+豌豆，所以默认可以解决
                        continue;
                    }
                }
            }
        }
        for (int i = 0; i < 5; i++) //如果解决不了，或者有雪橇车或者巨人，那么就动用倭瓜和辣椒
        {
            if (LeftLines[i] == 0)
            {
                continue;
            }
            if (CanResolve[i] == 0)
            {
                if (PlantCD[5] == 0 && Sun >= 50)
                {
                    player->PlacePlant(6, i, ZombiesAccurate[i][Nearest[i]][2] / 10);
                    PlantCD[5] = 60;
                    Sun -= 50;
                    continue;
                }
                if (PlantCD[4] == 0 && Sun >= 125)
                {
                    player->PlacePlant(5, i, 7);
                    PlantCD[4] = 60;
                    Sun -= 125;
                }
            }
        }
        for (int i = 0; i < 5; i++) //如果还剩有CD和阳光，那么自主种一些植物
        {
            if (LeftLines[i] == 0)
            {
                continue;
            }
            if (SunflowerNum[i] == 0 && Sun >= 150 && PlantCD[0] == 0)
            {
                player->PlacePlant(1, i, NearestPlant[i] + 1);
                NearestPlant[i]++;
                Sun -= 50;
                PlantCD[0] = 10;
            }
            if (PeashooterNum[i][0] == 0 && Sun > 350 && PlantCD[2] == 0)
            {
                player->PlacePlant(3, i, NearestPlant[i] + 1);
                NearestPlant[i]++;
                Sun -= 100;
                PlantCD[2] = 10;
            }
            if (PeashooterNum[i][1] == 0 && Sun > 600 && PlantCD[1] == 0)
            {
                player->PlacePlant(2, i, NearestPlant[i] + 1);
                NearestPlant[i]++;
                Sun -= 400;
                PlantCD[1] = 30;
            }
        }
        for (int i = 0; i < 5; i++)
        {
            if (LeftLines[i] == 0)
            {
                continue;
            }
            if (SunflowerNum[i] == 1 && Sun >= 150 && PlantCD[0] == 0)
            {
                player->PlacePlant(1, i, NearestPlant[i] + 1);
                NearestPlant[i]++;
                Sun -= 50;
                PlantCD[0] = 10;
            }
            if (PeashooterNum[i][0] == 1 && Sun > 250 && PlantCD[2] == 0)
            {
                player->PlacePlant(3, i, NearestPlant[i] + 1);
                NearestPlant[i]++;
                Sun -= 100;
                PlantCD[2] = 10;
            }
            if (PeashooterNum[i][1] == 1 && Sun > 600 && PlantCD[1] == 0)
            {
                player->PlacePlant(2, i, NearestPlant[i] + 1);
                NearestPlant[i]++;
                Sun -= 400;
                PlantCD[1] = 30;
            }
        }
        for (int i = 0; i < 5; i++)
        {
            if (LeftLines[i] == 0)
            {
                continue;
            }
            if (PlantCD[5] == 0 && SunflowerNum[i] == 2 && PeashooterNum[i][0] == 2 && PeashooterNum[i][1] == 2 && Sun > 200)
            {
                player->PlacePlant(6, i, 7);
            }
        }
        for (int i = 0; i < 5; i++) //将上一回合僵尸信息同步为这一回合僵尸信息
        {
            for (int j = 0; j < 10; j++)
            {
                for (int k = 0; k < 10; k++)
                {
                    Zombies[i][j][k] = -1;
                }
                for (int k = 0; ZombiesNow[i][j][k] != -1; k++)
                {
                    Zombies[i][j][k] = ZombiesNow[i][j][k];
                }
            }
        }
        for (int i = 0; i < 5; i++) //将上一回合植物信息同步为这一回合植物信息
        {
            for (int j = 0; j < 10; j++)
            {
                Plants[i][j] = PlantsNow[i][j];
            }
        }
    }
    else
    {
        player->PlaceZombie(1, 0);
        player->PlaceZombie(1, 1);
    }

if (Type == 1)
{

    int Rows = player->Camp->getRows();
    int Columns = player->Camp->getColumns();
    int Step = player->getTime();
    int *PlantCD = player->Camp->getPlantCD(); //僵尸CD;
    int** Plants = player->Camp->getCurrentPlants();
    int*** Zombies = player->Camp->getCurrentZombies();
    int *LeftLines = player->Camp->getLeftLines(); // LeftLines[i]==0 means broken
    int Sun = player->Camp->getSun();              //月光

    const int Plant_defense[7] = {0, 10, 60, 20, 40, 100, 30};
    const int Zombie_offense[6] = {0, 10, 30, 15, 60, 100};

    srand(player->getTime() + 1);

    int Line_flag[5] = {1};
    for (int i = 0; i < 5; i++)
    {
        if (Zombies[i][9][0] != -1 || LeftLines[i] == 0)
        {
            Line_flag[i] = 0;
        }
    }

    int Line_defense[5] = {0};
    int Nut_num[5] = {0};
    for (int i = 0; i < 5; i++)
    {
        if (LeftLines[i] == 0)
            Line_defense[i] = 10000;
        for (int j = 0; j < 10; j++)
        {
            Line_defense[i] += (int)(Plant_defense[Plants[i][j]] * 1.157 * (1 - pow(2.718, (-2 + j / 5.0))));
            if (Plants[i][j] == 6)
                Nut_num[i]++;
        }
    }

    int Line_offense[5] = {0};
    int Line_score[5] = {0};
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            for (int k = 0; Zombies[i][j][k] != -1; k++)
            {
                Line_offense[i] += (int)(Zombie_offense[Zombies[i][j][k]] * 1.157 * (1 - pow(2.718, (-2 + j / 5.0))));
            }
        }
        Line_score[i] = Line_offense[i] - Line_defense[i];
    }

    int Line_attack[5] = {rand() % 5, rand() % 5, rand() % 5, rand() % 5, rand() % 5};
    int Line_erase[1] = {rand() % 5};

    if (Step == 1)
    {
        player->PlaceZombie(1, 0);
        player->PlaceZombie(2, 1);
        player->PlaceZombie(3, 2);
    }
    else if (Step < 500) //试探+第一波
    {
        if (Step > 400 && Sun > 300)
        {
            player->PlaceZombie(5, Line_attack[0]);
            Sun -= 300;
        }

        if (Nut_num[Line_attack[0]] == 1 && Line_score[Line_attack[0]] > 30)
        {
            player->PlaceZombie(3, Line_attack[0]);
            Sun -= 125;
        }
        else
        {
            if (Sun >= 200 && Sun < 250 && Line_score[Line_attack[0]] > 30)
            {
                player->PlaceZombie(1, Line_attack[0]);
                Sun -= 50;
            }
            else
            {
                if (Sun >= 250)
                    player->PlaceZombie(2, Line_attack[0]);
            }
        }
    }

    else if (Step == 500) //分散冲
    {
        player->PlaceZombie(1, Line_attack[0]);
        Sun -= 50;

        if (Sun >= 150)
        {
            for (int i = 0; i < 5; i++) //撑杆跳偷家
            {
                if (Sun >= 150 && Line_defense[i] <= 10 && Line_offense[i] == 0)
                {
                    player->PlaceZombie(3, i);
                    Sun -= 125;
                }
            }
        }

        if (Sun >= 200)
        {
            player->PlaceZombie(2, Line_attack[1]);
            Sun -= 125;
        }
    }

    else if (Step > 500 && Step < 1000) //铁桶开路
    {
        if (Step < 550)
        {
            player->PlaceZombie(5, Line_erase[0]);
            Sun -= 300;
        }

        for (int i = 0; i < 5; i++) //撑杆跳偷家
        {
            if (Sun >= 150 && Line_defense[i] <= 10 && Line_offense[i] == 0)
            {
                player->PlaceZombie(3, i);
                Sun -= 125;
            }
        }

        if (Sun > 0)
            player->PlaceZombie(2, Line_attack[0]);
    }

    else if (Step == 1000) //一起冲 骗倭瓜和辣椒
    {
        player->PlaceZombie(1, Line_attack[0]);
    }
    else if (Step == 1005)
    {
        player->PlaceZombie(2, Line_attack[0]);
    }
    else if (Step == 1016)
    {
        player->PlaceZombie(1, Line_attack[0]);
    }
    else if (Step > 1016 && Step < 1500)
    {
        for (int i = 0; i < 5; i++) //撑杆跳偷家
        {
            if (Sun >= 150 && Line_defense[i] <= 10 && Line_offense[i] == 0)
            {
                player->PlaceZombie(3, i);
                Sun -= 125;
            }
        }

        if (Step < 1060)
        {
            player->PlaceZombie(5, Line_erase[0]);
            Sun -= 300;
        }

        if (Sun > 0)
            player->PlaceZombie(2, Line_attack[0]);
    }

    else if (Step == 1500) //冲两路或一路
    {
        player->PlaceZombie(1, Line_attack[0]);
        Sun -= 50;
        if (Sun >= 200)
        {
            player->PlaceZombie(2, Line_attack[0]);
            Sun -= 125;
        }
        if (Sun >= 150)
        {
            for (int i = 0; i < 5; i++) //撑杆跳偷家
            {
                if (Sun >= 150 && Line_defense[i] <= 10 && Line_offense[i] == 0)
                {
                    player->PlaceZombie(3, i);
                    Sun -= 125;
                }
            }
        }
    }
    else if (Step > 1500 && Step < 1900) //随机捡漏
    {
        int Zombie_type = rand() % 2 + 2;
        player->PlaceZombie(Zombie_type, Line_attack[0]);
        Zombie_type = rand() % 2 + 2;
        player->PlaceZombie(Zombie_type, Line_attack[1]);
        Zombie_type = rand() % 2 + 2;
        player->PlaceZombie(Zombie_type, Line_attack[2]);
    }
    else if (Step >= 1900 && Step <= 2000) //收官
    {
        for (int i = 0; i < 5; i++) //撑杆跳偷家
        {
            if (Sun >= 150 && Line_defense[i] <= 10 && Line_offense[i] == 0)
            {
                player->PlaceZombie(3, i);
                Sun -= 125;
            }
        }
        int Zombie_type = rand() % 2 + 2;
        player->PlaceZombie(Zombie_type, Line_attack[0]);
        player->PlaceZombie(5, Line_erase[0]);
    }
}
}
