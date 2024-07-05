#ifndef BULLET_H
#define BULLET_H

#include "common_agent.h"

class Bullet : public Agent {
    private:
    float bulletSpeed;
    int bulletDamage;

    public:
    Bullet(float speed, int damage);
    const int get_damage();

};

#endif