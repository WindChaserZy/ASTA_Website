#include "ai.h"

typedef struct tagPriority {
    int row;
    int col;
    int p;
} posAndPri;

typedef struct tagPPriAndType {
    posAndPri p;
    int type;
} PPriAndType;

// 该行是否有type1 和 type2
bool hasType(IPlayer* player, int row, int cols, int type1, int type2) {
    int*** Zombies = player->Camp->getCurrentZombies();
    for (int i = 0; i < cols; ++i) {
        int k = 0;
        while (Zombies[row][i][k] != -1) {
            if (Zombies[row][i][k] == type1 || Zombies[row][i][k] == type2) return true;
            k++;
        }
    }
    return false;
}

// 该行最前面的僵尸在哪里
int find_first_zombie(IPlayer* player, int row, int cols) {
    int*** Zombies = player->Camp->getCurrentZombies();
    int i = 0;
    while (i < cols && Zombies[row][i][0] == -1) i++;
    return i;
}

// 哪几行没有僵尸
int* no_zombie_rows(IPlayer* player, int cols) {
    int* rows = new int[5];
    for (int i = 0; i < 5; ++i)
        rows[i] = (find_first_zombie(player, i, cols) != cols);
    return rows;
}

// 估算一行的僵尸和植物的战力
int ForceCompare(int row, bool isZombie, IPlayer* player)
{
    int rows = player->Camp->getRows();
    int columns = player->Camp->getColumns();
    int turn = player->getTime();
    int BrokenLinesScore = player->getBrokenLinesScore();
    int NotBrokenLinesNum = player->getNotBrokenLines();
    int KillPlantsScore = player->getKillPlantsScore();
    int KillZombiesScore = player->getKillZombiesScore();
    int LeftPlants = player->getLeftPlants();
    int Score = player->getScore();
    int* PlantCD = player->Camp->getPlantCD();
    int** Plants = player->Camp->getCurrentPlants();
    int*** Zombies = player->Camp->getCurrentZombies();
    int* LeftLines = player->Camp->getLeftLines();
    int Sun = player->Camp->getSun();

    int sum = 0;
    if (isZombie)//计算僵尸的武力值
    {
        for (int i = 0; i < columns; i++)
        {
            int k = 0;
            while (Zombies[row][i][k] != -1)
            {
                //计算武力值时，让武力值和血量、速度成正比
                if (Zombies[row][i][k] == 1)//普通僵尸
                    sum += 270;//将普通僵尸作为标杆
                else if (Zombies[row][i][k] == 2)//铁桶僵尸
                    sum += 820;
                else if (Zombies[row][i][k] == 3)//撑杆跳僵尸
                    sum += 200 * 5 / 4.5;//这里是对撑杆僵尸的估算，个人觉得撑杆用处不大，故没有考虑在内
                else if (Zombies[row][i][k] == 4)//雪橇僵尸
                    sum += 1600 * 5 / 7;
                else if (Zombies[row][i][k] == 5)//巨人僵尸
                    sum += 3000;
                k++;
            }
        }
    }
    else
    {
        for (int j = 0; j < columns; j++)
        {
            if (Plants[row][j] == 2)//冰豌豆
                sum += j * 5 * 40;//普通僵尸走到跟前时造成的总伤害
            if (Plants[row][j] == 3)//豌豆
                sum += j * 5 * 10;
            if (Plants[row][j] == 4)//坚果墙
                sum += 53 * 10;//注：此处计算坚果墙武力值为估算，是在只有一个豌豆和一个僵尸情况下估算的
        }
    }
    return sum;
}

// 植物比僵尸强多少
int strongerThan(int row, IPlayer* player) {
    return ForceCompare(row, false, player) - ForceCompare(row, true, player);
}

// 返回差值数组
int* stronger_array(IPlayer* player) {
    int* stronger_arr = new int[5];
    for (int i = 0; i < 5; ++i) stronger_arr[i] = strongerThan(i, player);
    return stronger_arr;
}

// 最差的一列
int weakest_row(IPlayer* player) {
    int* LeftLines = player->Camp->getLeftLines();
    int* stronger_arr = stronger_array(player);
    int min = 0;
    int row = 0;
    for (int i = 0; i < 5; ++i) {
        if (LeftLines[i] == 1) {
            if (stronger_arr[i] < min) {
                min = stronger_arr[i];
                row = i;
            }
        }
    }
    return row;
}

// 是不是每一行都强
bool isPStronger(IPlayer* player) {
    bool isStronger = true;
    for (int i = 0; i < 5; ++i) {
        if (strongerThan(i, player) < 0) isStronger = false;
    }
    return isStronger;
}

// 最前面的植物
int front_col(IPlayer* player, int row) {
    int** plants = player->Camp->getCurrentPlants();
    int i = 0;
    while (plants[row][i] == 0) i++;
    return i;
}

//向日葵：前50回合优先度为1300
//       前200回合优先度为1200
//       如果所有植物都强势，那么优先度为1150
posAndPri Priority_sunflower(IPlayer* player) {

    int* PlantCD = player->Camp->getPlantCD();
    int cols = player->Camp->getColumns();
    int turn = player->getTime();
    int Sun = player->Camp->getSun();
    int** Plants = player->Camp->getCurrentPlants();

    int col = -1;
    int row = -1;
    int p = 0;

    if (turn < 50) {
        for (int i = 0; i < 5; ++i) {
            if (Plants[i][3] == 0) { row = i; col = 3; p = 1300; break; }
            if (Plants[i][4] == 0) { row = i; col = 4; p = 1300; break; }
        }
    }
    else if (turn < 200) {
        for (int i = 0; i < 5; ++i) {
            if (Plants[i][3] == 0) { row = i; col = 3; p = 1200; break; }
            if (Plants[i][4] == 0) { row = i; col = 4; p = 1200; break; }
        }
    }
    else if (isPStronger(player)) {
        for (int i = 0; i < 5; ++i) {
            if (Plants[i][3] == 0) { row = i; col = 3; p = 1150; break; }
            if (Plants[i][4] == 0) { row = i; col = 4; p = 1150; break; }
        }
    }

    if (Sun < 50) p = 0;
    if (PlantCD[0] != 0) p = 0;
    if (col == -1 || row == -1) return { 0, 0, 0 };
    else return { row, col, p };

}

posAndPri Priority_winterpeashooter(IPlayer* player) {
    int* PlantCD = player->Camp->getPlantCD();
    int Sun = player->Camp->getSun();
    int** Plants = player->Camp->getCurrentPlants();

    int p = 0;
    int row = 0;
    int col = 0;
    
    if (!isPStronger(player))//如果阳光比较少，节约一点
    {
        p = 900;
        row = weakest_row(player);
        if (Plants[row][2] == 0) col = 2;
        else if (Plants[row][4] == 0) col = 4;
        else col = -1;//没地方种了
    }
    else// 有余力时，摆满三列
    {
        int tmp[5] = {2, 5, 0, 1, 6};
        for(int j = 4; j >= 0; j--)
            for (int i = 0; i < 5; i++)
                if (Plants[i][tmp[j]] != 2)
                {
                    row = i;
                    col = tmp[j];
                    p = 550;
                }
    }
    if (PlantCD[1] != 0 || Sun < 500 || col == -1) p = 0;

    return { row, col, p };
}

posAndPri Priority_peashooter(IPlayer* player) {
    int* PlantCD = player->Camp->getPlantCD();
    int Sun = player->Camp->getSun();
    int** Plants = player->Camp->getCurrentPlants();

    int p = 0;
    int row = 0;
    int col = 0;
    if (!isPStronger(player))//如果阳光比较少，节约一点
    {
        p = 1050;
        row = weakest_row(player);
        if (Plants[row][0] == 0) col = 0;
        else if (Plants[row][1] == 0) col = 1;
        else col = -1;//没地方种了，以后可以在这里加入铲子
    }
    else// 有余力时，摆满一列
    {
        for (int j = 0; j < 2; j++)
            for (int i = 0; i < 5; i++)
            {
                if (Plants[i][j] == 0)
                {
                    row = i;
                    col = j;
                    p = 600;
                    break;
                }
            }
    }
    if (PlantCD[2] != 0 || Sun < 100 || col == -1 || Sun > 1000) p = 0;

    return { row, col, p };
}


void setBoss(posAndPri* Boss, int i, int j, int pri)
{
    Boss->row = i;
    Boss->col = j;
    Boss->p = pri;
}

//我的优先级（供参考）
//向日葵：前50回合优先度为1300
//       前200回合优先度为1200
//       如果所有植物都强势，那么优先度为1150
//冰豌豆：阳光比较少时，防御敌人，优先度为900
//       如果植物变得强势，种满三列，优先度为550
//豌豆：阳光比较少时，防御敌人，优先度为1050
//     如果植物变得强势，种满两列，优先度为600
//坚果墙：在前200回合，主动防御铁桶等僵尸，优先度1000
//       在后200回合，阳光高于450时补齐坚果墙，优先度800
//       在所有回合，如果僵尸进入了草坪两格，自动放坚果墙防御，优先级为1100
//       存在巨人和雪橇时，如果已经决定在这一行放置坚果，取消之
//倭瓜：存在巨人僵尸时，立即放置，优先度1200（应该很高）
//     如果一格内僵尸浓度很大，立即放置，优先度1150（也比较高）
//     如果快被打穿了，则立即放置倭瓜，优先度2000（应仅次于向日葵）
//辣椒：如果一行僵尸过于强大，放置辣椒，优先度1110
posAndPri Priority_smallnut(IPlayer* player)
{
    int rows = player->Camp->getRows();
    int columns = player->Camp->getColumns();
    int turn = player->getTime();
    int BrokenLinesScore = player->getBrokenLinesScore();
    int NotBrokenLinesNum = player->getNotBrokenLines();
    int KillPlantsScore = player->getKillPlantsScore();
    int KillZombiesScore = player->getKillZombiesScore();
    int LeftPlants = player->getLeftPlants();
    int Score = player->getScore();
    int* PlantCD = player->Camp->getPlantCD();
    int** Plants = player->Camp->getCurrentPlants();
    int*** Zombies = player->Camp->getCurrentZombies();
    int* LeftLines = player->Camp->getLeftLines();
    int Sun = player->Camp->getSun();

    posAndPri Boss = { 0, 0, 0 };
    //在开始时在保护战斗力弱的行
    if (turn < 200)
    {
        //检索是否有比较弱的行，种植坚果墙
        for (int i = 0; i < rows; i++)
            //种植坚果，如果一行出现了两个僵尸或者出现了铁桶僵尸
            if (Zombies[i][columns - 1][0] == 2 || Zombies[i][columns - 1][1] != -1)
                setBoss(&Boss, i, columns - 1, 1000);
    }
    else
    {
        //在战斗后期，自动补齐坚果墙
        for (int j = columns - 3; j <= columns - 1; j++)
            for (int i = 0; i < rows; i++)
                if (Plants[i][j] == 0 && Sun > 450 && LeftLines[i] == 1)//如果有多余阳光，且没有被攻破,则补齐一行坚果墙
                    setBoss(&Boss, i, j, 800);
    }
    //被动防御优先
    for (int j = 0; j < columns - 1; j++)
        for (int i = 0; i < rows; i++)
            if (Zombies[i][j][0] != -1)//如果僵尸攻入了内地
                setBoss(&Boss, i, j, 1100);
    //场上有巨人僵尸时，不放坚果墙
    if (Boss.p != 0)
    {
        for (int i = 0; i < columns; i++)
        {
            int k = 0;
            while (Zombies[Boss.row][i][k] != -1)
            {
                if (Zombies[Boss.row][i][k] == 4 || Zombies[Boss.row][i][k] == 5)
                    setBoss(&Boss, 0, 0, 0);
                k++;
            }
        }
        if (PlantCD[3] != 0) setBoss(&Boss, 0, 0, 0);//CD不够时，CD自动清零
    }
    return Boss;
}
//weakest_row
//以下是窝瓜和辣椒的函数
//the function of smallnut
//version 1.0

//一格的僵尸密集度
int denseOfZombie(IPlayer* player, int i, int j)
{
    int*** Zombies = player->Camp->getCurrentZombies();
    int sum = 0;
    int k = 0;
    while (Zombies[i][j][k] != -1)
    {
        if (Zombies[i][j][k] == 1) sum += 270;
        else if (Zombies[i][j][k] == 2) sum += 820;
        else if (Zombies[i][j][k] == 3) sum += 200 * 5 / 4.5;
        else if (Zombies[i][j][k] == 4) sum += 1600 * 5 / 7;
        else sum += 3000;
        k++;
    }
    return sum;
}

posAndPri Priority_squash(IPlayer* player)
{
    int rows = player->Camp->getRows();
    int columns = player->Camp->getColumns();
    int turn = player->getTime();
    int BrokenLinesScore = player->getBrokenLinesScore();
    int NotBrokenLinesNum = player->getNotBrokenLines();
    int KillPlantsScore = player->getKillPlantsScore();
    int KillZombiesScore = player->getKillZombiesScore();
    int LeftPlants = player->getLeftPlants();
    int Score = player->getScore();
    int *PlantCD = player->Camp->getPlantCD();
    int** Plants = player->Camp->getCurrentPlants();
    int*** Zombies = player->Camp->getCurrentZombies();
    int* LeftLines = player->Camp->getLeftLines();
    int Sun = player->Camp->getSun();

    posAndPri Boss = {0,0,0};
    for(int i = 0;i < rows;i++)
    {
        for(int j = 0;j < columns;j++)
        {
            int k = 0;
            //砸巨人僵尸
            while(Zombies[i][j][k] != -1)
            {
                if (Zombies[i][j][k] == 5 && Boss.p < 1500)
                {
                    setBoss(&Boss, i, j, 1500);
                }//碰到巨人僵尸的优先度,the second hightest, only lower than sunflower
                if (denseOfZombie(player, i, j) > 1100 && ForceCompare(i, true, player) < ForceCompare(i, false, player) && Boss.p < 1150)
                    setBoss(&Boss, i, j, 1150);//碰到一大坨僵尸且一行没有足够的战力时的的优先度,优先级应次于添加攻击性植物
                k++;
            }
            //绝地反击，如果僵尸快打穿了
            if (j == 1 && Zombies[i][1][0] != -1 && Boss.p < 2000)
                setBoss(&Boss, i, 1, 2000);//此地逻辑存疑，待修正
        }
    }
    if (PlantCD[5] != 0 || Sun < 50) Boss.p = 0;
    return Boss;
}

posAndPri Priority_pepper(IPlayer* player)
{
    int rows = player->Camp->getRows();
    int columns = player->Camp->getColumns();
    int turn = player->getTime();
    int BrokenLinesScore = player->getBrokenLinesScore();
    int NotBrokenLinesNum = player->getNotBrokenLines();
    int KillPlantsScore = player->getKillPlantsScore();
    int KillZombiesScore = player->getKillZombiesScore();
    int LeftPlants = player->getLeftPlants();
    int Score = player->getScore();
    int *PlantCD = player->Camp->getPlantCD();
    int** Plants = player->Camp->getCurrentPlants();
    int*** Zombies = player->Camp->getCurrentZombies();
    int* LeftLines = player->Camp->getLeftLines();
    int Sun = player->Camp->getSun();

    posAndPri Boss = {0,0,0};
    for(int i=0;i<rows;i++)
    {
        if (ForceCompare(i, true, player) - 800 > ForceCompare(i, false, player)
            || ForceCompare(i, true, player) > 1700)
            setBoss(&Boss, i, columns - 1, 1100);//优先级应该较高
    }
    if (PlantCD[4] != 0 || Sun < 125) Boss.p = 0;
    return Boss;
}
//zombies' functions

// 获取僵尸最佳放置的row值
int get_best_y(IPlayer* player, int CurrentAct)
{
    int columns = player->Camp->getColumns();
    int** Plants = player->Camp->getCurrentPlants();

    int Priorityofy[5] = { 0 };
    if (CurrentAct < 4)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < columns; i++)
            {
                switch (Plants[j][i])
                {
                case 0:
                    break;
                case 1:
                    Priorityofy[j]++;
                    break;
                case 2:
                    Priorityofy[j] -= 2;
                    break;
                case 3:
                case 4:
                    Priorityofy[j]--;
                    break;
                case 5:
                    Priorityofy[j] -= 5;
                    break;
                case 6:
                    Priorityofy[j] -= 2;
                    break;
                }
            }
        }
    }
    else {
        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < columns; i++)
            {
                switch (Plants[j][i]) {
                case 0:
                    break;
                case 1:
                    Priorityofy[j] += 2;
                    break;
                case 2:
                    Priorityofy[j] -= 1;
                    break;
                case 3:
                case 4:
                    break;
                case 5:
                    Priorityofy[j] -= 5;
                    break;
                case 6:
                    Priorityofy[j] -= 2;
                    break;
                }
            }
        }
    }
    int Besty = 0;
    int BestValue = Priorityofy[0];
    for (int i = 1; i < 5; i++)
    {
        if (Priorityofy[i] > BestValue) {
            Besty = i;
            BestValue = Priorityofy[i];
        }
    }
    return Besty;
}

posAndPri Priority_normal(IPlayer* player) {
    int p = 0;

    int turn = player->getTime();
    int sun = player->Camp->getSun();
    int* PlantCD = player->Camp->getPlantCD();

    if (turn < 1000) {
        p += 2;
    }
    if (turn > 1000) {
        p += (turn - 1000) / 150;
        // zombies' blood and attack increased and it's better for the blood-low.
    }

    if (sun < 50 || PlantCD[0] != 0) p = 0;
    return { get_best_y(player, 1), -1, p };
}

posAndPri Priority_bucket(IPlayer* player) {
    int rows = player->Camp->getRows();
    int columns = player->Camp->getColumns();
    int turn = player->getTime();
    int* PlantCD = player->Camp->getPlantCD();
    int** Plants = player->Camp->getCurrentPlants();
    int Sun = player->Camp->getSun();

    int p = 0;
    if (Sun > 150 && Sun <= 400) {
        p += Sun / 50;
    }
    if (turn > 1000) {
        p += (turn - 1000) / 180;
        // zombies' blood and attack increased and it's better for the blood-low.
    }
    for (int i = 0; i < rows; i++)
    {
        int thisrowsituation = 0;
        for (int j = 0; j < columns; j++)
        {
            if (Plants[i][j] == 1 || Plants[i][j] == 3) {
                thisrowsituation += (4 - Plants[i][j]);
            }
        }
        if (thisrowsituation >= 3) {
            p += 3;
            //if there are many peashooters and sunflowers, we need buckets to kill them for the moon
        }
    }
    if (Sun < 125 || PlantCD[1] != 0) p = 0;
    return { get_best_y(player, 2), -1, p };
}

posAndPri Priority_polevault(IPlayer* player) {
    int rows = player->Camp->getRows();
    int columns = player->Camp->getColumns();
    int turn = player->getTime();
    int* PlantCD = player->Camp->getPlantCD();
    int** Plants = player->Camp->getCurrentPlants();
    int Sun = player->Camp->getSun();

    int p = 0;

    if (Sun >= 75 && Sun < 300) {
        p += Sun / 56;
    }
    // we think polevault is faster and more economic than normal,so it's better
    for (int i = 0; i < rows; i++)
    {
        for (int j = 1; j < columns; j++)
        {
            if (Plants[i][j] == 4 || Plants[i][j] == 6) {
                p++;
                // if the plant is smallnut or squash, we need polevault to jump over
            }
        }
    }
    if (PlantCD[2] == 0) {
        p += 4;
    }
    if (turn % 500 == 0) {
        p += 2;
        // a buff of zombies 
    }
    if (turn > 1000) {
        p += (turn - 1000) / 200;
        // zombies' blood and attack increased and it's better for the blood-low.
    }

    if (Sun < 75 || PlantCD[2] != 0) p = 0;
    return { get_best_y(player, 3), -1, p };
}

posAndPri Priority_sled(IPlayer* player) {
    int rows = player->Camp->getRows();
    int columns = player->Camp->getColumns();
    int* PlantCD = player->Camp->getPlantCD();
    int** Plants = player->Camp->getCurrentPlants();
    int SumoffrontPlants = 0;
    int Sun = player->Camp->getSun();

    int p = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 5; j < columns; j++)
        {
            if (Plants[i][j]) {
                SumoffrontPlants++;
            }
        }
    }
    if (SumoffrontPlants >= 2) {
        p += SumoffrontPlants - 1;
        // there are many plants in the front ,so the sled can kill them faster in the front
    }
    if (PlantCD[3] == 0) {
        p += 3;
    }
    if (Sun < 300 || PlantCD[3] != 0) p = 0;
    return { get_best_y(player, 4), -1, p };
}

posAndPri Priority_gargantuar(IPlayer* player) {
    int rows = player->Camp->getRows();
    int columns = player->Camp->getColumns();
    int turn = player->getTime();
    int* PlantCD = player->Camp->getPlantCD();
    int** Plants = player->Camp->getCurrentPlants();
    int Sun = player->Camp->getSun();
    int p = 0;

    if (Sun > 300) {
        p += (Sun - 200) / 100;
    }
    //if you have many moonlight, then kill the plants once for sure
    for (int i = 0; i < rows; i++)
    {
        int thisrowsituation = 0;
        for (int j = 0; j < columns; j++)
        {
            if (Plants[i][j] == 3 || Plants[i][j] == 2) {
                thisrowsituation += (4 - Plants[i][j]);
            }
        }
        if (thisrowsituation >= 3) {
            p += 3;
            //if there are many peashooters and winterpeashooters, we need gargantuar to kill them for the moon
        }
    }
    if (PlantCD[4] == 0) {
        p += 4;
    }
    // no CD, no waiting
    if (turn % 500 == 0) {
        p += 3;
        // a buff of zombies 
    }
    if (Sun < 300 || PlantCD[4] != 0) p = 0;
    return { get_best_y(player, 5), -1, p };
}

// 返回最佳的植物或僵尸
PPriAndType get_target(IPlayer* player) {
    int type = player->Camp->getCurrentType();
    if (type == 0) {
        posAndPri arr[6];
        arr[0] = Priority_sunflower(player);
        arr[1] = Priority_winterpeashooter(player);
        arr[2] = Priority_peashooter(player);
        arr[3] = Priority_smallnut(player);
        arr[4] = Priority_pepper(player);
        arr[5] = Priority_squash(player);

        posAndPri best = arr[0];
        int t = 1;
        for (int i = 1; i < 6; ++i)
            if (arr[i].p > best.p) {
                best = arr[i];
                t = i + 1;
            }
        return { best, t };

    }
    else {
        posAndPri arr[5];
        arr[0] = Priority_normal(player);
        arr[1] = Priority_bucket(player);
        arr[2] = Priority_polevault(player);
        arr[3] = Priority_sled(player);
        arr[4] = Priority_gargantuar(player);
        int t = 1;
        posAndPri best = arr[0];
        for (int i = 0; i < 5; ++i) {
            if (arr[i].p > best.p) {
                best = arr[i];
                t = i + 1;
            }
        }
        return { best, t };
    }
};

void removePeashooter(IPlayer* player, PPriAndType pt)//铲子
{
    int** Plants = player->Camp->getCurrentPlants();
    if (pt.type == 2 && Plants[pt.p.row][pt.p.col] != 2)
        player->removePlant(pt.p.row, pt.p.col);
}

void player_ai(IPlayer* player)
{
    // 获取植物方还是僵尸方
    int Type = player->Camp->getCurrentType();

    if (Type == 0)//植物方
    {
        PPriAndType pt = get_target(player);
        removePeashooter(player, pt);
        if (pt.p.p > 0) player->PlacePlant(pt.type, pt.p.row, pt.p.col);
    }

    if (Type == 1)//僵尸方
    {
        PPriAndType pt = get_target(player);
        if (pt.p.p > 0) player->PlaceZombie(pt.type, pt.p.row);
    }
}