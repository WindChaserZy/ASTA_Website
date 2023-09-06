#include "ai.h"
#include <iostream>


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
void player_ai(IPlayer * player)
{
    // player code here
}