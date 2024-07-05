#include "client_player.h"
#define ALIVE_STATE 0
#define INITIAL_POINTS 0
#define INITIAL_HP 100.0
#define MIN_HP 0

Player::Player(int posX, int posY): equippedGun(20 , 10, 10, 10)
{
    currentLife = INITIAL_HP;
    status = ALIVE_STATE;
    points = INITIAL_POINTS;
    this->posX = posX;
    this->posY = posY;
}

void Player::shoot()
{
}

void Player::run()
{
}

void Player::jump()
{
}

void Player::runFast()
{
}

void Player::applyDamage(int damage)
{
    if (currentLife > MIN_HP)
    {
        currentLife -= damage;
    }
}

void Player::revive()
{
    status = ALIVE_STATE;
    currentLife = INITIAL_HP;
}

void Player::increasePoints(int numberOfPoints)
{
    points += numberOfPoints;
}
