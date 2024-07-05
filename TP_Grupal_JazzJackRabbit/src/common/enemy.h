#ifndef ENEMY_H
#define ENEMY_H

#include "common_agent.h"

class Enemy : public Agent
{
private:
    int status;
    int maxLife;
    int damage;
    int points;
    int respawnTime;
    int probabilityAmmunition;
    int probabilityLife;

public:
    Enemy(int maxLife, int damage, int points, int respawnTime, int probabilityAmmunition, int probabilityLife, int posX, int posY);
    void die();
    void revive(int respawnPointX, int respawnPointY);
};

#endif
