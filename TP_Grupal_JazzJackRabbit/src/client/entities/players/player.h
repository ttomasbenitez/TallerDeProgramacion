#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include "client_gun.h"
#include "common_agent.h"

class Player : public Agent
{
private:
    int status;
    int points;
    std::vector<Gun> guns;
    Gun equippedGun;

public:
    Player(int posX, int posY);
    void shoot();
    void run();
    void jump();
    void runFast();
    void applyDamage(int damage);
    void revive();
    void increasePoints(int numberOfPoints);
    int getPoints();
    int getStatus();

    virtual void specialAttack() = 0;
};
#endif
