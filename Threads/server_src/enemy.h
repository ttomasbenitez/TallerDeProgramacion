#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#define ITERATIONS_TO_REVIVE 15

class Enemy {
private:
    bool alive;
    int iterations_dead;

public:
    Enemy();
    bool is_alive();
    bool revive();
    void receive_attack();
    ~Enemy() = default;
};


#endif  // ENEMY_H
