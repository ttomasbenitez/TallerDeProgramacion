#include "client_gun.h"
#define MIN_AMMO 0
#define AMMO_USAGE 1

Gun::Gun(int numAmmunition, int shootingSpeed, int projectileSpeed, int damage)
{
    this->numAmmunition = numAmmunition;
    this->shootingSpeed = shootingSpeed;
    this->projectileSpeed = projectileSpeed;
    this->damage = damage;
}

void Gun::shoot()
{
    if (numAmmunition > MIN_AMMO)
        numAmmunition -= AMMO_USAGE;
}

void Gun::addAmmunition(int numAmmunition)
{

    this->numAmmunition += numAmmunition;
}

bool Gun::hasAmmunition()
{
    return numAmmunition > MIN_AMMO;
}

int Gun::getDamage()
{
    return damage;
}

int Gun::getShootingSpeed()
{
    return shootingSpeed;
}

int Gun::getProjectileSpeed()
{
    return projectileSpeed;
}
