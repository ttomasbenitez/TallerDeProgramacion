#include "client_bullet.h"

Bullet::Bullet(float speed, int damage){
    bulletSpeed = speed;
    bulletDamage = damage;
}

const int Bullet::get_damage(){
    return bulletDamage;
}