#include "enemy.h"

Enemy::Enemy(): alive(true), iterations_dead(0) {}

bool Enemy::is_alive() { return alive; }

bool Enemy::revive() {

    if (iterations_dead >= ITERATIONS_TO_REVIVE) {
        alive = true;
        iterations_dead = 0;
        return true;
    }

    iterations_dead++;
    return false;
}

void Enemy::receive_attack() { alive = false; }
