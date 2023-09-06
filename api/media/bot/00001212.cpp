#include "ai.h"
#include <iostream>
int help = 0;
int offend = 0;
bool had_xueqiao[5] = { 0 };
bool detect_guaorjiao[5] = { 0 };
int had_jiagang[5] = { 0 };
int lajiao[5] = { 0 };
int all_xueqiao[5] = { 0 };
bool filledd = 0;
int needpea = -1;
void updateplants(int, int, int, int&, int*, int**);
int Plants_cur[5][10];
int Sunflower_planttime[5][10];
int Plant_sun = 400;

int zombiePH(int m_type) {
    switch (m_type)
    {
    case 0: return 0;
        break;
    case 1:return 270;
        break;
    case 2:return 1370;
        break;
    case 3: return 500;
        break;
    case 4:return 1350;
        break;
    case 5:return 3000;
        break;
    default:
        break;
    }
}

int PlantAttack(int m_type) {
    switch (m_type)
    {
    case 0:return 0;
        break;
    case 1:return 0;
        break;
    case 2:return 26;
        break;
    case 3:return 20;
        break;
    case 4:return 0;
        break;
    case 5:return 1800;
        break;
    case 6:return 1800;
        break;
    default:
        break;
    }
}

void player_ai(IPlayer* player) {
    int Type = player->Camp->getCurrentType(); //获取植物方还僵尸方
    int BrokenLinesScore = player->getBrokenLinesScore();
    int NotBrokenLinesNum = player->getNotBrokenLines();
    int KillPlantsScore = player->getKillPlantsScore();
    int KillZombiesScore = player->getKillZombiesScore();
    int LeftPlants = player->getLeftPlants();
    int Score = player->getScore();
    int time = player->getTime();
    int rows = player->Camp->getRows();
    int columns = player->Camp->getColumns();
    int* PlantCD = player->Camp->getPlantCD();
    int** Plants = player->Camp->getCurrentPlants();
    int*** Zombies = player->Camp->getCurrentZombies();
    int* LeftLines = player->Camp->getLeftLines();
    int Sun = player->Camp->getSun();
    if (Type == 0) {
        //当前为植物方，采取若干策略
        //v3.9
        if (time >= 800) {
            PlantCD[3] = 100;
            PlantCD[2] = 100;
        }

        int gargantuar[10] = { 0 };
        int sled[10] = { 0 };
        int polevault[10] = { 0 };
        int bucket[10] = { 0 };
        int normal[10] = { 0 };
        int zombienum[5] = { 0 };
        int zombieplace[5] = { 0 };
        int dangerplace[5] = { 0 };
        int numplace[5] = { 0 };
        int bucketplace[5] = { 0 };
        int poleplace[5] = { 0 };
        bool rowok[5] = { 0 };
        int sfnum[5] = { 0 }, peanum[5] = { 0 }, winternum[5] = { 0 }, nutnum[5] = { 0 }, wgnum[5] = { 0 };
        int dangerrow[5] = { -1,-1,-1,-1,-1 };
        bool sunfull = 1;
        int garplace[5] = { 0 };
        for (int i = 0; i < rows; i++)
        {
            int k = 0;
            gargantuar[i] = 0;
            sled[i] = 0;
            polevault[i] = 0;
            bucket[i] = 0;
            normal[i] = 0;
            zombienum[i] = 0;
            zombieplace[i] = 10;
            dangerplace[i] = 11;
            numplace[i] = -1;
            poleplace[i] = -1;
            bucketplace[i] = -1;
            garplace[i] = -1;
            for (int j = 0; j < columns; j++)
            {
                k = 0;
                while (Zombies[i][j][k] != -1)
                {
                    switch (Zombies[i][j][k])
                    {
                    case 1:normal[i]++; break;
                    case 2:bucket[i]++;
                        if (bucketplace[i] == -1)
                        {
                            bucketplace[i] = j;
                        }
                        break;
                    case 3:polevault[i]++;
                        if (poleplace[i] == -1)
                        {
                            poleplace[i] = j;
                        }
                        break;
                    case 4: {
                        sled[i]++;
                        if (dangerplace[i] == 11)
                        {
                            dangerplace[i] = j;
                        }
                        break;
                    }
                    case 5: {
                        gargantuar[i]++;
                        if (dangerplace[i] == 11)
                        {
                            dangerplace[i] = j;
                        }
                        if (garplace[i] == -1) {
                            garplace[i] = j;
                        }
                        break;
                    }
                    default:break;
                    }
                    k++;
                    zombienum[i]++;
                }
                if (k >= 2 && numplace[i] == -1)
                {
                    numplace[i] = j;
                }
                if (zombieplace[i] == 10 && Zombies[i][j][0] != -1)
                {
                    zombieplace[i] = j;
                }
            }
        }
        for (int i = 0; i < 5; i++)
        {
            if (LeftLines[i] != 0)
            {
                int cur_row = i;
                for (int j = 0; j < columns - 1; j++)
                {
                    if (Plants[cur_row][j] == 1)
                    {
                        sfnum[cur_row]++;
                    }
                    else if (Plants[cur_row][j] == 2 || Plants[cur_row][j] == 3)
                    {
                        peanum[cur_row]++;
                        if (Plants[cur_row][j] == 2)
                            winternum[cur_row]++;
                    }
                }
                for (int j = 5; j < columns; j++)
                {
                    if (Plants[cur_row][j] == 4)
                        nutnum[cur_row]++;
                    else if (Plants[cur_row][j] == 6)
                        wgnum[cur_row]++;
                }
            }
        }
        bool selectrow[5] = { 0 };
        for (int i = 0; i < rows; i++)
        {
            int currow = -1;
            for (int j = 0; j < rows; j++)
            {
                if (selectrow[j] || LeftLines[j] == 0)
                    continue;
                if (currow == -1)
                {
                    currow = j;
                    continue;
                }
                if (gargantuar[j] > gargantuar[currow])
                    currow = j;
                else if (gargantuar[j] == gargantuar[currow])
                {
                    if (sled[currow] < sled[j])
                        currow = j;
                    else if (sled[currow] == sled[j])
                    {
                        if (zombienum[j] > zombienum[currow])
                            currow = j;
                        else if (zombienum[j] == zombienum[currow])
                        {
                            if (bucket[j] > bucket[currow])
                                currow = j;
                            else if (bucket[j] == bucket[currow])
                            {
                                if (polevault[j] > polevault[currow])
                                    currow = j;
                                else if (polevault[j] == polevault[currow])
                                {
                                    if (normal[j] > normal[currow])
                                        currow = j;
                                    else if (normal[j] == normal[currow])
                                    {
                                        if (winternum[j] < winternum[currow])
                                            currow = j;
                                        else if (winternum[j] == winternum[currow])
                                        {
                                            if (peanum[j] < peanum[currow])
                                                currow = j;
                                            else if (peanum[j] == peanum[currow])
                                            {
                                                if (sfnum[j] < sfnum[currow])
                                                {
                                                    currow = j;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                
            }
            dangerrow[i] = currow;
            selectrow[currow] = 1;
        }
        for (int i = 0; i < 5; i++)
        {
            int cur_row = dangerrow[i];
            int min = dangerrow[i];
            bool needpea = 1;
            bool defendd = 0;
            bool usedsquar = 0;
            if (cur_row != -1 && LeftLines[cur_row] >= 0)
            {
                for (int i = 0; i < zombieplace[cur_row]; i++)
                {
                    if (Plants[cur_row][i] == 2 || Plants[cur_row][i] == 3 || Plants[cur_row][i] == 4)
                    {
                        defendd = 1;
                        break;
                    }
                }
                bool pea = peanum[cur_row], sunflower = sfnum[cur_row], nut = nutnum[cur_row], wg = wgnum[cur_row];
                if (sunflower && (((normal[min] || polevault[min] || bucket[min]) && pea) || !(normal[min] || polevault[min] || bucket[min])))
                {
                    rowok[min] = 1;
                }
                if (polevault[min] != 0&&time<400)
                {
                    bool yyee = 0;
                    for (int j = columns - 1; j >= poleplace[min]; j--)
                    {
                        if (Plants[min][j] != 0)
                        {
                            yyee = 1;
                            break;
                        }
                    }
                    if (yyee == 0)
                    {
                        if (poleplace[min] >= 7)
                        {
                            if (((Sun >= 50 && pea) || ((PlantCD[2] == 0 || (poleplace[min] == 8 && PlantCD[2] <= 4) || (poleplace[min] >= 9 && PlantCD[2] <= 9)) && Sun >= 150)) && PlantCD[3] == 0 && Plants[min][poleplace[min] - 1] == 0)
                            {
                                player->PlacePlant(4, min, poleplace[min] - 1);
                                updateplants(4, min, poleplace[min] - 1, Sun, PlantCD, Plants);
                                if (!pea && PlantCD[2] == 0)
                                {
                                    for (int j = 0; j < 3; j++)
                                    {
                                        if (Plants[min][j] == 0)
                                        {
                                            player->PlacePlant(3, min, poleplace[min] - 1);
                                            updateplants(3, min, poleplace[min] - 1, Sun, PlantCD, Plants);
                                            pea = 1;
                                            break;
                                        }
                                    }
                                }
                            }
                            else if (((Sun >= 50 && pea) || ((PlantCD[2] == 0 || (poleplace[min] == 8 && PlantCD[2] <= 4) || (poleplace[min] >= 9 && PlantCD[2] <= 9)) && Sun >= 150)) && PlantCD[0] == 0 && Plants[min][poleplace[min] - 1] == 0)
                            {
                                player->PlacePlant(1, min, poleplace[min] - 1);
                                updateplants(1, min, poleplace[min] - 1, Sun, PlantCD, Plants);
                                if (!pea && PlantCD[2] == 0)
                                {
                                    for (int j = 0; j < 3; j++)
                                    {
                                        if (Plants[min][j] == 0)
                                        {
                                            player->PlacePlant(3, min, poleplace[min] - 1);
                                            updateplants(3, min, poleplace[min] - 1, Sun, PlantCD, Plants);
                                            pea = 1;
                                            break;
                                        }
                                    }
                                }
                            }
                            else if (Sun >= 50 && PlantCD[5] == 0 && Plants[min][poleplace[min]] == 0 && time < 400)
                            {
                                bool yyeee = 1;
                                for (int i = 5; i < columns; i++)
                                {
                                    if (Plants[cur_row][i] != 0)
                                    {
                                        yyeee = 0;
                                        break;
                                    }
                                }
                                if (yyeee)
                                {
                                    player->PlacePlant(6, min, poleplace[min]);
                                    updateplants(6, min, poleplace[min], Sun, PlantCD, Plants);
                                    needpea = 0;
                                }
                            }
                        }
                        else {
                            if (Sun >= 50 && PlantCD[5] == 0 && Plants[min][poleplace[min] - 1] == 0 && time < 400)
                            {
                                player->PlacePlant(6, min, poleplace[min] - 1);
                                updateplants(6, min, poleplace[min] - 1, Sun, PlantCD, Plants);
                                needpea = 0;
                            }
                        }
                    }
                }
                
                if (bucket[min] != 0 && time <= 400)
                {
                    bool okk = 0;
                    
                    if (PlantCD[5] == 0 && Sun >= 50 && Plants[min][bucketplace[min]] == 0 && !nut && wg == 0 && ((Plants[min][bucketplace[min] - 1] != 0 && Plants[min][bucketplace[min] - 1] != 4) || !defendd))
                    {
                        player->PlacePlant(6, min, bucketplace[min]);
                        updateplants(6, min, bucketplace[min], Sun, PlantCD, Plants);
                        wg = 1;
                        okk = 1;
                        needpea = 0;
                    }
                    if (!okk && PlantCD[3] == 0 && Sun >= 50 && !nut && !wg && bucketplace[cur_row] < 9)
                    {
                        for (int j = bucketplace[min]-1; j >= 0; j--)
                        {
                            if (Plants[min][j] == 0)
                            {
                                player->PlacePlant(4, min, j);
                                updateplants(4, min, j, Sun, PlantCD, Plants);
                                break;
                            }
                        }
                    }
                }
                if ((normal[min] != 0 || polevault[min] != 0 || bucket[min] != 0) && needpea&&(!wg&&time<200) && Sun >= 100 && PlantCD[2] == 0 && !pea && (zombieplace[min] >= 7 || (Sun >= 150 && PlantCD[3] == 0) || nut || (Zombies[min][zombieplace[min]][0] == 3 && zombieplace[min] >= 6)))
                {
                    int j = 0;
                    for (; j < 5 && j < zombieplace[min]; j++)
                    {
                        if (Plants[min][j] == 0)
                        {
                            player->PlacePlant(3, min, j);
                            updateplants(3, min, j, Sun, PlantCD, Plants);
                            pea = 1;
                            break;
                        }
                    }
                    
                }
                if (sled[cur_row] + gargantuar[cur_row] > 0)
                {
                    if (gargantuar[cur_row] != 0 || winternum[cur_row] < 3||dangerplace[cur_row]<=5)
                    {
                        int dangerpoint = dangerplace[cur_row];
                        if (winternum[cur_row] >= 3)
                        {
                            dangerpoint = garplace[cur_row];
                        }
                        if (PlantCD[5] == 0 && Sun >= 50 && (Plants[cur_row][dangerpoint] == 0 || (dangerpoint - 1 >= 0 && (Plants[cur_row][dangerpoint - 1] == 0 || Plants[cur_row][dangerpoint - 1] == 1))))
                        {
                            if (dangerpoint - 1 >= 0 && (Plants[cur_row][dangerpoint - 1] == 0 || Plants[cur_row][dangerpoint - 1] == 1))
                            {
                                if (Plants[cur_row][dangerpoint - 1] == 1)
                                {
                                    player->removePlant(cur_row, dangerpoint - 1);
                                }
                                player->PlacePlant(6, cur_row, dangerpoint - 1);
                                updateplants(6, cur_row, dangerpoint - 1, Sun, PlantCD, Plants);
                            }
                            else {
                                player->PlacePlant(6, cur_row, dangerpoint);
                                updateplants(6, cur_row, dangerpoint, Sun, PlantCD, Plants);
                            }
                        }
                        else if (PlantCD[4] == 0 && Sun >= 125 && PlantCD[5] < 60 &&((dangerpoint <= 5&&Sun<4000)||(dangerpoint<=3)) && ((dangerpoint - 1 >= 0 && Plants[cur_row][dangerpoint - 1] != 0 && Plants[cur_row][dangerpoint - 1] != 4)))
                        {
                            for (int i = columns - 1; i >= 0; i--)
                            {
                                if (Plants[cur_row][i] == 0)
                                {
                                    player->PlacePlant(5, cur_row, dangerpoint);
                                    updateplants(5, cur_row, dangerpoint, Sun, PlantCD, Plants);
                                    usedsquar = 1;
                                    break;
                                }
                            }
                        }
                    }
                }
                if (polevault[cur_row] + bucket[cur_row] >= 2 && Plants[cur_row][zombieplace[cur_row] - 1] != 0 && Plants[cur_row][zombieplace[cur_row] - 1] != 4 && Sun >= 125 && PlantCD[4] == 0&&time<300)
                {
                    for (int j = columns; j >= 0; j--)
                    {
                        if (Plants[cur_row][j] == 0)
                        {
                            player->PlacePlant(5, cur_row, j);
                            updateplants(5, cur_row, j, Sun, PlantCD, Plants);
                            break;
                        }
                    }
                }
                bool okeyy = 0;
                if (numplace[cur_row] != -1 && time <= 300)
                {
                    if (Plants[cur_row][numplace[cur_row]] == 0)
                    {
                        if (PlantCD[5] == 0 && Sun >= 50)
                        {
                            player->PlacePlant(6, cur_row, numplace[cur_row]);
                            updateplants(6, cur_row, numplace[cur_row], Sun, PlantCD, Plants);
                            okeyy = 1;
                        }
                    }
                }
                if (okeyy == 0&&time<=300)
                {
                    if (zombienum[cur_row] >= 3 && (Plants[cur_row][zombieplace[cur_row]] != 0 && Plants[cur_row][zombieplace[cur_row]] != 4) && PlantCD[4] == 0 && Sun >= 175 && PlantCD[5] < 60)
                    {
                        for (int j = 0; j < columns; j++)
                        {
                            if (Plants[cur_row][j] == 0)
                            {
                                player->PlacePlant(5, cur_row, j);
                                updateplants(5, cur_row, j, Sun, PlantCD, Plants);
                                break;
                            }
                        }
                    }
                }
                
                if (zombieplace[cur_row] == 0&&!usedsquar)
                {
                    int numm = 0;
                    while (Zombies[cur_row][0][numm] != -1)
                        numm++;
                    if (zombienum[cur_row] > numm) {
                        if (PlantCD[4] == 0 && Plants[cur_row][0] == 0 && Sun >= 125)
                        {
                            player->PlacePlant(5, cur_row, 0);
                            updateplants(5, cur_row, 0, Sun, PlantCD, Plants);
                        }
                        else if (PlantCD[5] == 0 && Plants[cur_row][0] == 0 && Sun >= 50)
                        {
                            player->PlacePlant(6, cur_row, 0);
                            updateplants(6, cur_row, 0, Sun, PlantCD, Plants);
                        }
                    }
                    else {
                        if (PlantCD[5] == 0 && Plants[cur_row][0] == 0 && Sun >= 50)
                        {
                            player->PlacePlant(6, cur_row, 0);
                            updateplants(6, cur_row, 0, Sun, PlantCD, Plants);
                        }
                        else if (PlantCD[4] == 0 && Plants[cur_row][0] == 0 && Sun >= 125)
                        {
                            player->PlacePlant(5, cur_row, 0);
                            updateplants(5, cur_row, 0, Sun, PlantCD, Plants);
                        }
                    }
                }
                else if (!usedsquar&&zombieplace[cur_row] <= 4 &&(Zombies[cur_row][zombieplace[cur_row]][0] != 1||!defendd) && (Plants[cur_row][zombieplace[cur_row] - 1] == 1 || Plants[cur_row][zombieplace[cur_row] - 1] == 2 || Plants[cur_row][zombieplace[cur_row] - 1] == 3))
                {
                    if (PlantCD[5] == 0 && Sun >= 100 && Plants[cur_row][zombieplace[cur_row]] == 0)
                    {
                        player->PlacePlant(6, cur_row, zombieplace[cur_row]);
                        updateplants(6, cur_row, zombieplace[cur_row], Sun, PlantCD, Plants);
                    }
                }
                if (!nut && (zombieplace[cur_row] == 5 || zombieplace[cur_row] == 6) &&(Zombies[cur_row][zombieplace[cur_row]][0] != 1&&defendd) && Zombies[cur_row][zombieplace[cur_row]][0] != 3 && time <= 400)
                {
                    for (int j = 5; j < zombieplace[cur_row]; j++)
                    {
                        if (Plants[cur_row][j] == 0)
                        {
                            if (Sun >= 100 && PlantCD[3] == 0)
                            {
                                player->PlacePlant(4, cur_row, j);
                                updateplants(4, cur_row, j, Sun, PlantCD, Plants);
                                break;
                            }
                            else break;
                        }
                    }
                }
                else if (!nut && zombieplace[cur_row] <= 4)
                {
                    for (int j = zombieplace[cur_row]-1; j >= 0; j--)
                    {
                        if (Plants[cur_row][j] == 4)
                        {
                            nut = 1;
                            break;
                        }
                    }
                    if (!nut && zombienum[min])
                    {
                        int tmpp = zombieplace[cur_row];
                        if (Plants[cur_row][tmpp] == 0 && PlantCD[3] == 0 && Sun >= 50 && pea == 1)
                        {
                            player->PlacePlant(4, cur_row, tmpp);
                            updateplants(4, cur_row, tmpp, Sun, PlantCD, Plants);
                        }
                    }
                }
            }
            else if (cur_row != -1)
                rowok[min] = 1;
        }
        for (int i = 4; i >= 0; i--)
        {
            int min = dangerrow[i];
            if (min == -1)
                continue;
            bool pea = peanum[min];
            if (Sun >= 50 && PlantCD[0] == 0 && sfnum[min] <= 1)
            {
                int j = 1;
                for (; j < 5 && j < zombieplace[min]; j++)
                {
                    if (Plants[min][j] == 0)
                    {
                        player->PlacePlant(1, min, j);
                        updateplants(1, min, j, Sun, PlantCD, Plants);
                        break;
                    }
                }
            }
        }
        if (time >= 100)
        {
            for (int i = 0; i < columns; i++)
            {
                if (LeftLines[i] == 1 && sfnum[i] < 2)
                    sunfull = 0;
            }
            if (time >= 700)
                sunfull = 1;
            for (int i = 0; i < 5; i++)
            {
                int workline = dangerrow[i];
                if (workline == -1)
                    break;
                if (time >= 200)
                {
                    
                    if (zombienum[workline] == 0)
                    {
                        for (int i = 0; i < 5; i++)
                        {
                            if (Plants[workline][i] == 4)
                            {
                                player->removePlant(workline, i);
                                updateplants(0, workline, i, Sun, PlantCD, Plants);
                            }
                        }
                        for (int i = 0; i < 5; i++)
                        {
                            if (Plants[workline][i] == 6)
                            {
                                player->removePlant(workline, i);
                                updateplants(0, workline, i, Sun, PlantCD, Plants);
                            }
                        }
                    }
                }
                if (workline != -1)
                {
                    if (peanum[workline] < 3 && PlantCD[2] == 0 && Sun >= 150)
                    {
                        if (Sun < 650&&(peanum[workline]<2||zombienum))//
                        {
                            for (int i = 0; i < 5; i++)
                            {
                                if (Plants[workline][i] == 0)
                                {
                                    player->PlacePlant(3, workline, i);
                                    updateplants(3, workline, i, Sun, PlantCD, Plants);
                                    break;
                                }
                            }
                        }
                        else if(Sun>=650&&PlantCD[1]==0) {
                            for (int i = 0; i < 5; i++)
                            {
                                if (Plants[workline][i] == 0)
                                {
                                    player->PlacePlant(2, workline, i);
                                    updateplants(2, workline, i, Sun, PlantCD, Plants);
                                    break;
                                }
                            }
                        }
                    }
                    else if (peanum[workline] >= 3 && PlantCD[1] == 0 && Sun >= 500)
                    {
                        for (int i = 0; i <= 5; i++)
                        {
                            if (Plants[workline][i] == 3 || Plants[workline][i] == 0||(Sun>=1000&&Plants[workline][i]==1))
                            {
                                if (Plants[workline][i])
                                {
                                    player->removePlant(workline, i);
                                }
                                player->PlacePlant(2, workline, i);
                                updateplants(2, workline, i, Sun, PlantCD, Plants);

                                break;
                            }
                        }
                    }
                    if (sfnum[workline] == 1 && PlantCD[0] == 0 && Sun >= 50)
                    {
                        for (int i = 1; i < 5&&i<zombieplace[workline]; i++)
                        {
                            if (Plants[workline][i] == 0)
                            {
                                player->PlacePlant(1, workline, i);
                                updateplants(1, workline, i, Sun, PlantCD, Plants);
                                break;
                            }
                        }
                    }
                    if (sunfull && PlantCD[0] == 0 && Sun >= 50 && sfnum[workline] < 3)
                    {
                        for (int i = 5; i < zombieplace[workline]-1; i++)
                        {
                            if (Plants[workline][i] == 0)
                            {
                                player->PlacePlant(1, workline, i);
                                updateplants(1, workline, i, Sun, PlantCD, Plants);
                                break;
                            }
                        }
                    }
                    if (nutnum[workline] >= 2 && Sun >= 75 && PlantCD[0] == 0 && sfnum[workline] <= 2 && peanum[workline] >= 2)
                    {
                        for (int i = 0; i < columns; i++)
                        {
                            if (Plants[workline][i] == 4)
                            {
                                player->removePlant(workline, i);
                                player->PlacePlant(1, workline, i);
                                updateplants(1, workline, i, Sun, PlantCD, Plants);
                                break;
                            }
                        }
                    }
                    if (Sun >= 800 && sfnum[workline] >= 3 && PlantCD[1] == 0)
                    {
                        for (int i = 0; i < columns; i++)
                        {
                            if (Plants[workline][i] == 1 || Plants[workline][i] == 0)
                            {
                                if (Plants[workline][i] == 1)
                                    player->removePlant(workline, i);
                                player->PlacePlant(2, workline, i);
                                updateplants(2, workline, i, Sun, PlantCD, Plants);
                                break;
                            }
                        }
                    }
                    if (Sun >= 175 && PlantCD[5] == 0 && PlantCD[4] <= 5 && wgnum[workline] == 0&&!zombienum[workline])
                    {
                        if (time <= 350)
                        {
                            bool nplace = 0;
                            int nuuplace = 10;
                            for (int i = columns - 1; i > 5; i--)
                            {
                                if (Plants[workline][i] == 4)
                                {
                                    nplace = 1;
                                    nuuplace = i;
                                    break;
                                }
                            }
                            if (nplace == 1 && nuuplace >= 2)
                            {
                                for (int i = nuuplace - 2; i > 5; i--)
                                {
                                    if (Plants[workline][i] == 0 || Plants[workline][i] == 4)
                                    {
                                        if (Plants[workline][i] == 4)
                                            player->removePlant(workline, i);
                                        player->PlacePlant(6, workline, i);
                                        updateplants(6, workline, i, Sun, PlantCD, Plants);
                                        break;
                                    }
                                }
                            }
                        }
                        else {
                            for (int i = 6; i < columns; i++)
                            {
                                if (Plants[workline][i] == 0 || Plants[workline][i] == 4)
                                {
                                    if (Plants[workline][i] == 4)
                                        player->removePlant(workline, i);
                                    player->PlacePlant(6, workline, i);
                                    updateplants(6, workline, i, Sun, PlantCD, Plants);
                                    break;
                                }
                            }
                        }
                    }
                }
                if (dangerplace[workline] != 11 && (Plants[workline][dangerplace[workline] - 1] == 1 || Plants[workline][dangerplace[workline] - 1] == 3 || Plants[workline][dangerplace[workline] - 1] == 4))
                    player->removePlant(workline, dangerplace[workline] - 1);
            }
            if (time >= 500 && PlantCD[0] == 0&&Sun>=50)
            {
                for (int i = 4; i >= 0; i--)
                {
                    if (dangerrow[i] == -1)
                        continue;
                    int workline = dangerrow[i];
                    for (int j = 7; j < zombieplace[workline]-1 && j < columns; j++)
                    {
                        if (Plants[workline][j] == 0)
                        {
                            player->PlacePlant(1, workline, j);
                            updateplants(1, workline, j, Sun, PlantCD, Plants);
                            break;
                        }
                    }
                    if (PlantCD[0])
                        break;
                }
            }
            if (time >= 500 && nutnum[time % 5])
            {
                for (int i = 5; i < columns; i++)
                {
                    if (Plants[time % 5][i] == 4)
                        player->removePlant(time % 5, i);
                }
            }
        }
    }


    // ======================================================================
    // ======================================================================


    if (Type == 1) {
        //当前为僵尸方,采取若干策略
        // v4.12

                // 扫描当前植物情况
        int wandou[5] = { 9999,9999,9999,9999,9999 };
        int hanbin[5] = { 9999,9999,9999,9999,9999 };
        int jianguo[5] = { 9999,9999,9999,9999,9999 };
        int wogua[5] = { 9999,9999,9999,9999,9999 };
        int xiangrikui[5] = { 9999,9999,9999,9999,9999 };
        int all_plants[5] = { 9999,9999,9999,9999,9999 };
        double weighted_average_qianqi[5] = { 9999,9999,9999,9999,9999 };
        double weighted_average_zhongqi_xiangrikui[5] = { 9999,9999,9999,9999,9999 };
        double weighted_average_zhongqi[5] = { 9999,9999,9999,9999,9999 };
        bool need_attack[5] = { 1,1,1,1,1 };
        for (int i = 0; i < rows; ++i) {
            if (LeftLines[i] == 0 || Zombies[i][0][0] != -1) {
                need_attack[i] = false;
            }
        }
        for (int i = 0; i < rows; ++i) {
            if (!need_attack[i]) continue;
            wandou[i] = 0;
            hanbin[i] = 0;
            jianguo[i] = 0;
            wogua[i] = 0;
            xiangrikui[i] = 0;
            all_plants[i] = 0;
        }
        for (int i = 0; i < rows; ++i) {
            if (!need_attack[i]) continue;
            for (int j = 0; j < columns; ++j) {
                if (Plants[i][j] == 0) {
                    Plants_cur[i][j] = 0;
                }
                else {
                    if (Plants[i][j] != Plants_cur[i][j]) {
                        Plants_cur[i][j] = Plants[i][j];
                        switch (Plants[i][j]) {
                        case 1:
                            Plant_sun -= 50;
                            Sunflower_planttime[i][j] = time;
                            break;
                        case 2:
                            Plant_sun -= 400;
                            break;
                        case 3:
                            Plant_sun -= 100;
                            break;
                        case 4:
                            Plant_sun -= 50;
                            break;
                        case 5:
                            Plant_sun -= 125;
                            break;
                        case 6:
                            Plant_sun -= 50;
                            break;
                        case 0:
                            break;
                        }
                    }
                }
                if (Plants[i][j] == 2) hanbin[i]++;
                if (Plants[i][j] == 3) wandou[i]++;
                if (Plants[i][j] == 4) jianguo[i]++;
                if (Plants[i][j] == 6) wogua[i]++;
                if (Plants[i][j] == 1) xiangrikui[i]++;
                if (Plants[i][j] == 5) lajiao[i]++;

            }
            all_plants[i] = wandou[i] + hanbin[i] + jianguo[i] + wogua[i] + xiangrikui[i];
        }
        int min_wandou = 999, min_wandou_i = -1;
        int min_hanbin = 999, min_hanbin_i = -1;
        int min_jianguo = 999, min_jianguo_i = -1;
        int max_xiangrikui = 0, max_xiangrikui_i = -1;
        for (int i = 0; i < rows; ++i) {
            if (!need_attack[i])  continue;
            if (wandou[i] < min_wandou) {
                min_wandou = wandou[i];
                min_wandou_i = i;
            }
            if (hanbin[i] < min_hanbin) {
                min_hanbin = hanbin[i];
                min_hanbin_i = i;
            }
            if (jianguo[i] < min_jianguo) {
                min_jianguo = jianguo[i];
                min_jianguo_i = i;
            }
            if (xiangrikui[i] >= max_xiangrikui) {
                max_xiangrikui = xiangrikui[i];
                max_xiangrikui_i = i;
            }
        }

        // 检查当前僵尸状况
        int zombies[5] = { 0,0,0,0,0 };
        int tietong[5] = { 0,0,0,0,0 };
        int chenggan[5] = { 0,0,0,0,0 };
        int xueqiao[5] = { 0,0,0,0,0 };
        int jiagang[5] = { 0,0,0,0,0 };
        double all_zombies[5] = { 0,0,0,0,0 };
        for (int i = 0; i < rows; ++i) {
            if (!need_attack[i]) continue;
            for (int j = 0; j < columns; ++j) {
                for (int k = 0; Zombies[i][j][k] != -1; ++k) {
                    if (Zombies[i][j][k] == 1) zombies[i]++;
                    if (Zombies[i][j][k] == 2) tietong[i]++;
                    if (Zombies[i][j][k] == 3) chenggan[i]++;
                    if (Zombies[i][j][k] == 4) {
                        xueqiao[i]++; all_xueqiao[i]++;
                    }
                    if (Zombies[i][j][k] == 5) jiagang[i]++;
                }
            }
            all_zombies[i] = 0.2 * zombies[i] + 0.5 * tietong[i] + 0.3 * chenggan[i] + 0.6 * xueqiao[i] + 1.0 * jiagang[i];
        }

        // 对场上情况将进行估计
        double min_weighted_average_qianqi = 999;
        int min_weighted_average_qianqi_i = -1;
        double min_weighted_average_zhongqi_xiangrikui = 999;
        int min_weighted_average_zhongqi_xiangrikui_i = -1;
        double min_weighted_average_zhongqi = 999;
        int min_weighted_average_zhongqi_i = -1;
        for (int i = 0; i < rows; ++i) {
            // warning：当前估值函数，以及后续采用的阈值为大致估计，需结合实战回访重新制定
             // TODO:火爆辣椒对参数加成的影响导致bug（伽刚和雪橇出现在了两行）,有空再改吧
            weighted_average_qianqi[i] = 1.0 * wogua[i] + 0.6 * hanbin[i] + 0.3 * jianguo[i] + 0.1 * wandou[i] + 0.1 * lajiao[i];
            if (all_plants[i] == xiangrikui[i] && all_zombies[i] > 0) weighted_average_qianqi[i] = 999;
            if (weighted_average_qianqi[i] <= min_weighted_average_qianqi) {
                min_weighted_average_qianqi = weighted_average_qianqi[i];
                min_weighted_average_qianqi_i = i;
            }
            weighted_average_zhongqi_xiangrikui[i] = 0.3 * wogua[i] + 0.7 * hanbin[i] + 0.3 * jianguo[i] + 0.7 * xiangrikui[i] + 0.15 * lajiao[i];
            if (weighted_average_zhongqi_xiangrikui[i] < min_weighted_average_zhongqi_xiangrikui) {
                min_weighted_average_zhongqi_xiangrikui = weighted_average_zhongqi_xiangrikui[i];
                min_weighted_average_zhongqi_xiangrikui_i = i;
            }
            weighted_average_zhongqi[i] = 0.3 * wogua[i] + 1.0 * hanbin[i] + 0.3 * jianguo[i] + 0.15 * lajiao[i];
            if (weighted_average_zhongqi[i] < min_weighted_average_zhongqi) {
                min_weighted_average_zhongqi = weighted_average_zhongqi[i];
                min_weighted_average_zhongqi_i = i;
            }
        }

        int target = -1;

        // 前期策略  回合<=200 或者 威胁<0.6
        target = max_xiangrikui_i;
        if (target == -1 || weighted_average_qianqi[target] > min_weighted_average_qianqi) {
            target = min_weighted_average_qianqi_i;
        }
        if (target == -1) return;
        if ((time <= 200 && weighted_average_qianqi[target] < 0.8) || (time > 200 && weighted_average_qianqi[target] < 0.6)) {
            if (Zombies[target][columns - 1][0] == -1) { // 根据场上情况放置僵尸，以攻击力植物为导向，针对主要进攻行
                for (int i = 0; i < rows; ++i) {
                    if (xiangrikui[i] > 1 && weighted_average_qianqi[i] == 0) {
                        player->PlaceZombie(2, i);
                        break;
                    }
                }
                
                

                int flag_i = -1;
                for (int i = 0; i < rows; ++i) {
                    if (all_plants[i] == (xiangrikui[i] + wogua[i]) && (all_zombies[i] <= wogua[i])) {
                        target = i;
                        flag_i = i;
                        break;
                    }
                }
                if (flag_i != -1) {
                    if (all_zombies[target] <= wogua[target] && Zombies[target][columns - 1][0] == -1) {
                        if (PlantCD[0] == 0 && Sun > 50 && Plant_sun < 100) {
                            player->PlaceZombie(1, target);
                        }
                        else {
                            player->PlaceZombie(2, target);
                        }
                    }
                }

                if (Zombies[target][columns - 1][0] == -1) {
                    if (wandou[target] > 0 && wandou[target] <= 1 && jianguo[target] > 0 && tietong[target] > 0 && chenggan[target] == 0) {
                        player->PlaceZombie(3, target);
                    }
                    if (weighted_average_qianqi[target] == 0 && all_zombies[target] == 0) {
                        if (Plant_sun < 100) { player->PlaceZombie(1, target); }
                        else { player->PlaceZombie(2, target); }
                    }
                    else {
                        if (hanbin[target] == 0) {
                            if (jianguo[target] > 0 && weighted_average_qianqi[target] < 0.5) player->PlaceZombie(3, target);
                            if ((2 * tietong[target] + zombies[target] + 1 * chenggan[target]) <= wandou[target]) {
                                if ((weighted_average_qianqi[target] + 0.6) > all_zombies[target]) {
                                    if (PlantCD[1] == 0) {
                                        player->PlaceZombie(2, target);
                                    }
                                    else {
                                        player->PlaceZombie(1, target);
                                    }
                                }
                                else {
                                    player->PlaceZombie(1, target);
                                }
                            }
                            int jianguo_place = -1;
                            for (int j = columns - 1; j >= 0; --j) {
                                if (Plants[target][j] == 4) {
                                    jianguo_place = j;
                                    break;
                                }
                            }
                            if (Zombies[target][columns - 1][0] == -1)
                                if (jianguo[target] > 0 && jianguo_place < 5 && tietong[target] > 0 && chenggan[target] == 0) player->PlaceZombie(3, target);
                        }
                        else {
                            if ((2 * tietong[target] + zombies[target]) <= (hanbin[target] + 2 + 2 * jianguo[target])) {
                                if (PlantCD[1] == 0) {
                                    player->PlaceZombie(2, target);
                                }
                            }
                        }
                    }
                }
            }

        }


        if (weighted_average_qianqi[target] > 0.6) { // 威胁>0.4

            // 中期策略（400-499（可能）空档期，用以积累阳光)  time 200-800
            if (((time > 200 && time <= 800) && !(time > 400 && time <= 499 && Sun < 500)) || (time <= 200 && weighted_average_qianqi[target] > 0.8)) {
                target = min_weighted_average_zhongqi_i;
                if (weighted_average_qianqi[target] < 0.6) { // 风险较小的情况下用普通僵尸/铁桶僵尸尝试攻击，沿用前期策略
                    if (Zombies[target][columns - 1][0] == -1) { // 根据场上情况放置僵尸，以攻击力植物为导向，针对主要进攻行
                        if (weighted_average_qianqi[target] == 0 && all_zombies[target] == 0) {
                            if (Zombies[target][columns - 1][0] == -1)player->PlaceZombie(1, target);
                        }
                        else {
                            if (hanbin[target] == 0) {
                                if (jianguo[target] > 0)
                                    if (Zombies[target][columns - 1][0] == -1)player->PlaceZombie(3, target);
                                if ((2 * tietong[target] + zombies[target] + 1 * chenggan[target]) <= wandou[target]) {
                                    if ((weighted_average_qianqi[target] + 0.6) > all_zombies[target]) {
                                        if (Zombies[target][columns - 1][0] == -1)player->PlaceZombie(2, target);
                                    }
                                    else {
                                        if (Zombies[target][columns - 1][0] == -1)player->PlaceZombie(1, target);
                                    }
                                }
                            }
                            else {
                                if ((2 * tietong[target] + zombies[target]) <= (hanbin[target] + 2 + 2 * jianguo[target])) {
                                    if (PlantCD[1] == 0) {
                                        if (Zombies[target][columns - 1][0] == -1)player->PlaceZombie(2, target);
                                    }
                                }
                            }
                        }
                    }
                }
                else { // 风险较大的情况
                    //if (Plants[target][columns - 1] == 6 || Plants[target][columns - 2] == 6) {
                    //    if (Zombies[target][columns - 1][0] == -1)player->PlaceZombie(3, target);
                    //}
                    if (hanbin[target] == 0) {
                        if (weighted_average_zhongqi[target] <= 1) {
                            if ((jiagang[target] == 0) || (jiagang[target] > 0 && weighted_average_zhongqi[target] > 0.7))
                                if (Zombies[target][columns - 1][0] == -1)player->PlaceZombie(5, target);
                        }
                        else {
                            if (Sun >= 600 && PlantCD[3] == 0 && PlantCD[4] == 0) {
                                if (Zombies[target][columns - 1][0] == -1) {
                                    player->PlaceZombie(4, target);
                                    offend = time;
                                }
                            }
                            if (PlantCD[3] >= 4 && Zombies[target][9][0] == -1) {
                                if ((jiagang[target] == 0) || (jiagang[target] > 0 && weighted_average_zhongqi[target] > 0.7))
                                    if (Zombies[target][columns - 1][0] == -1)player->PlaceZombie(5, target);
                            }
                        }

                    }
                    else {
                        if (Sun >= 600 && PlantCD[3] == 0 && PlantCD[4] == 0) {
                            if (Zombies[target][columns - 1][0] == -1) {
                                player->PlaceZombie(4, target);
                                offend = time;
                            }
                        }
                        if (PlantCD[3] >= 4 && Zombies[target][9][0] == -1) {
                            if ((jiagang[target] == 0) || (jiagang[target] > 0 && weighted_average_zhongqi[target] > 0.7))
                                if (Zombies[target][columns - 1][0] == -1)player->PlaceZombie(5, target);
                        }
                    }
                }
            }
            bool too_strong = false;
            // 中后期 800 - 1200 回合 以及 500 - 599回合（向日葵为导向的攻击模式）
            target = min_weighted_average_zhongqi_xiangrikui_i;
            if (target == -1) return;
            if ((time > 800 && time <= 1200) || (time > 500 && time <= 599)) {
                // std::cout << time << "\n";
                if (hanbin[target] <= 3) {
                    for (int j = 0; j < columns; ++j) {
                        if (Plants[target][j] == 5 || Plants[target][j] == 6) {
                            detect_guaorjiao[target] = true;
                            break;
                        }
                    }
                    if (weighted_average_qianqi[target] < 0.6) { // 风险较小的情况下用普通僵尸/铁桶僵尸尝试攻击，沿用前期策略
                        if (Zombies[target][columns - 1][0] == -1) { // 根据场上情况放置僵尸，以攻击力植物为导向，针对主要进攻行
                            if (weighted_average_qianqi[target] == 0 && all_zombies[target] == 0) {
                                player->PlaceZombie(1, target);
                            }
                            else {
                                if (hanbin[target] == 0) {
                                    if (jianguo[target] > 0) player->PlaceZombie(3, target);
                                    if ((2 * tietong[target] + zombies[target] + 1 * chenggan[target]) <= wandou[target]) {
                                        if (weighted_average_qianqi[target] > all_zombies[target]) {
                                            player->PlaceZombie(2, target);
                                        }
                                        else {
                                            player->PlaceZombie(1, target);
                                        }
                                    }
                                }
                                else {
                                    if ((2 * tietong[target] + zombies[target]) <= (hanbin[target] + 2 + 2 * jianguo[target])) {
                                        if (PlantCD[1] == 0) {
                                            player->PlaceZombie(2, target);
                                        }
                                        else {
                                            player->PlaceZombie(1, target);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else { // 风险较大的情况
                        if (Plants[target][columns - 1] == 6 || Plants[target][columns - 2] == 6) {
                            if (hanbin[target] == 0)
                                if (Zombies[target][columns - 1][0] == -1) {
                                    player->PlaceZombie(3, target);
                                }
                        }
                        else {
                            if (tietong[target] == 0 && (offend - time) > 15)
                                if (Zombies[target][columns - 1][0] == -1) {
                                    player->PlaceZombie(2, target);
                                    offend = time;
                                }
                            if (tietong[target] > 0 && (offend - time) > 2)
                                if (Zombies[target][columns - 1][0] == -1)player->PlaceZombie(3, target);
                        }
                        if (weighted_average_zhongqi[target] <= 0.8) {
                            if ((jiagang[target] == 0) || (jiagang[target] > 0 && weighted_average_zhongqi[target] > 0.7))
                                if (Zombies[target][columns - 1][0] == -1)player->PlaceZombie(5, target);
                        }
                        else {
                            if (Sun >= 600 && PlantCD[3] == 0 && PlantCD[4] == 0) {
                                if (Zombies[target][columns - 1][0] == -1)
                                {
                                    player->PlaceZombie(4, target);
                                    offend = time;
                                }
                            }
                            if (PlantCD[3] >= 3 && Zombies[target][9][0] == -1) {
                                if ((jiagang[target] == 0) || (jiagang[target] > 0 && weighted_average_zhongqi[target] > 0.7))
                                    if (Zombies[target][columns - 1][0] == -1) {
                                        player->PlaceZombie(5, target);
                                    }
                                if (Zombies[target][columns - 1][0] == -1 && hanbin[target] < 3)player->PlaceZombie(2, target);
                            }
                        }
                    }
                }
            }
            // 中后期 time>1200（寒冰射手为导向的攻击模式）
            target = min_hanbin_i;
            if (target == -1) return;
            if (time > 1200 ||hanbin[target] > 3) {
                if (hanbin[target] >= 4 ) {
                    
                    if (time >= 1500 ) {
                        
                        if (Sun >= 800 ||  PlantCD[1] != 0) {

                            if (Zombies[target][columns - 1][0] == -1)player->PlaceZombie(2, target);
                            if (Zombies[target][columns - 1][0] == -1)player->PlaceZombie(3, target);
                            if (Zombies[target][columns - 1][0] == -1)player->PlaceZombie(4, target);
                            if (Zombies[target][columns - 1][0] == -1)player->PlaceZombie(5, target);
                        }
                    }
                }
                else if(hanbin[target] <= 4) {
                    
                    for (int j = 0; j < columns; ++j) {
                        if (Plants[target][j] == 5 || Plants[target][j] == 6) {
                            detect_guaorjiao[target] = true;
                            break;
                        }
                    }
                    if (weighted_average_qianqi[target] < 0.6) { // 风险较小的情况下用普通僵尸/铁桶僵尸尝试攻击，沿用前期策略
                        if (Zombies[target][columns - 1][0] == -1) { // 根据场上情况放置僵尸，以攻击力植物为导向，针对主要进攻行
                            if (weighted_average_qianqi[target] == 0 && all_zombies[target] == 0) {
                                player->PlaceZombie(1, target);
                            }
                            else {
                                if (hanbin[target] == 0) {
                                    if (jianguo[target] > 0) player->PlaceZombie(3, target);
                                    if ((2 * tietong[target] + zombies[target] + 1 * chenggan[target]) <= wandou[target]) {
                                        if (weighted_average_qianqi[target] > all_zombies[target]) {
                                            player->PlaceZombie(2, target);
                                        }
                                        else {
                                            player->PlaceZombie(1, target);
                                        }
                                    }
                                }
                                else {
                                    if ((2 * tietong[target] + zombies[target]) <= (hanbin[target] + 2 + 2 * jianguo[target])) {
                                        if (PlantCD[1] == 0) {
                                            player->PlaceZombie(2, target);
                                        }
                                        else {
                                            player->PlaceZombie(1, target);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else { // 风险较大的情况
                        if (Plants[target][columns - 1] == 6) {
                            if (Zombies[target][columns - 1][0] == -1) {
                                player->PlaceZombie(3, target);
                            }
                        }
                        else if (Plants[target][columns - 2] == 6) {
                            if (tietong[target] == 0 && (offend - time) > 15)
                                if (Zombies[target][columns - 1][0] == -1) {
                                    player->PlaceZombie(2, target);
                                    offend = time;
                                }
                            if (tietong[target] > 0 && (offend - time) > 2)
                                if (Zombies[target][columns - 1][0] == -1)player->PlaceZombie(3, target);
                        }
                        if (weighted_average_zhongqi[target] <= 0.8) {
                            if ((jiagang[target] == 0) || (jiagang[target] > 0 && weighted_average_zhongqi[target] > 0.7))
                                if (Zombies[target][columns - 1][0] == -1)player->PlaceZombie(5, target);
                        }
                        else {
                            if (Sun >= 600 && PlantCD[3] == 0 && PlantCD[4] == 0) {
                                if (Plants[target][columns - 1] != 4 && Plants[target][columns - 2] != 4)player->PlaceZombie(2, target);
                                if (Zombies[target][columns - 1][0] == -1) {
                                    player->PlaceZombie(4, target);
                                    offend = time;
                                }
                            }
                            if (PlantCD[3] >= 3 && Zombies[target][9][0] == -1) {
                                if ((jiagang[target] == 0) || (jiagang[target] > 0 && weighted_average_zhongqi[target] > 0.7))
                                    if (Zombies[target][columns - 1][0] == -1)player->PlaceZombie(5, target);
                                if (Zombies[target][columns - 1][0] == -1 && hanbin[target] < 3)player->PlaceZombie(2, target);
                            }
                        }
                    }
                }
            }
        }
    }
}
void updateplants(int type, int x, int y, int& a, int* b, int** c)
{
    switch (type)
    {
    case 0:c[x][y] = 0; break;
    case 1:a -= 50; b[0] = 10; c[x][y] = 1; break;
    case 2:a -= 400; b[1] = 30; c[x][y] = 2; break;
    case 3:a -= 100; b[2] = 10; c[x][y] = 3; break;
    case 4:a -= 50; b[3] = 40; c[x][y] = 4; break;
    case 5:a -= 125; b[4] = 60; c[x][y] = 5; break;
    case 6:a -= 50; b[5] -= 60; c[x][y] = 6; break;
    default:break;
    }
}