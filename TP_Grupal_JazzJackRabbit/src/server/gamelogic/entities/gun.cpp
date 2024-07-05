#include "gun.h"


Gun::Gun(int numAmmunition, int shootingSpeed, int projectileSpeed, int damage, int capacity, AnimationState bulletType, AnimationState bulletSound):
    numAmmunition(numAmmunition), shootingSpeed(shootingSpeed), projectileSpeed(projectileSpeed),
    damage(damage), capacity(capacity), bulletType(bulletType), bulletSound(bulletSound){
        this->counter=5/shootingSpeed+1;
    }

std::unique_ptr<BulletEntity> Gun::shoot(float x, float y, int direction){
    if (capacity != -1)
    {
        numAmmunition--;
    }
    return std::make_unique<BulletEntity>(x, y, projectileSpeed*direction, damage, bulletType);
}

void Gun::addAmmunition(int amount){
    if (capacity == -1)
    {
        return;
    }
    ((numAmmunition <= capacity) && (numAmmunition + amount > capacity)) ? numAmmunition = capacity : numAmmunition += amount;
}

bool Gun::hasAmmunition(){
    if (numAmmunition == -1)
    {
        return true;
    }
    return numAmmunition > 0;
}

AnimationState Gun::getType(){
    return bulletType;
}

AnimationState Gun::getSoundType(){
    return bulletSound;
}

int Gun::magSize(){
    return capacity;
}

int Gun::currentAmmo(){
    return numAmmunition;
}

void Gun::resetShooting(){
    counter += 5/shootingSpeed+1;
}

bool Gun::canShoot(){
    if (counter < 5/shootingSpeed)
    {
        return false;
    }
    counter = 0;
    return true;
    
}

void Gun::tick(){
    ++counter;
}