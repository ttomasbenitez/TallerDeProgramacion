#ifndef GUN_H
#define GUN_H
class Gun
{
private:
    int numAmmunition;
    int shootingSpeed;
    int projectileSpeed;
    int damage;

public:
    Gun(int numAmmunition, int shootingSpeed, int projectileSpeed, int damage);
    void shoot();
    void addAmmunition(int numAmmunition);
    bool hasAmmunition();
    int getDamage();
    int getShootingSpeed();
    int getProjectileSpeed();
};
#endif
