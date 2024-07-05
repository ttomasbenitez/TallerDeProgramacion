#include "enemy.h"
#define DEAD_STATE -1
#define ALIVE_STATE 0
#define MIN_HP 0

Enemy::Enemy(int maxLife, int damage, int points, int respawnTime, int probabilityAmmunition, int probabilityLife, int posX, int posY)
{
    this->status = ALIVE_STATE;
    this->maxLife = maxLife;
    this->currentLife = maxLife;
    this->damage = damage;
    this->points = points;
    this->respawnTime = respawnTime;
    this->probabilityAmmunition = probabilityAmmunition;
    this->probabilityLife = probabilityLife;
    this->posX = posX;
    this->posY = posY;
}

void Enemy::die()
{
    currentLife = MIN_HP;
    status = DEAD_STATE; 
}

void Enemy::revive(int respawnPointX, int respawnPointY)
{
    this->posX = respawnPointX;
    this->posY = respawnPointY;
    currentLife = maxLife;
    this->status = ALIVE_STATE;
}
