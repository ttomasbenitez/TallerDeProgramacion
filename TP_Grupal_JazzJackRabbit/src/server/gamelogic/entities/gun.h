#ifndef GUN_H
#define GUN_H
#include "bullet.h"
#include <memory>


class Gun
{
protected:
    int numAmmunition;
    int shootingSpeed;
    int projectileSpeed;
    int damage;
    int capacity;
    AnimationState bulletType;
    AnimationState bulletSound;
    int counter;
public:
    Gun(int numAmmunition, int shootingSpeed, int projectileSpeed, int damage, int capacity,  AnimationState bulletType, AnimationState bulletSound);
    std::unique_ptr<BulletEntity> shoot(float x, float y, int direction);
    AnimationState getType();
    AnimationState getSoundType();
    void addAmmunition(int amount);
    int currentAmmo();
    bool hasAmmunition();
    int magSize();
    bool canShoot();
    void tick();
    void resetShooting();
};


#endif
