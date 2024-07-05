#ifndef ENTITY_DAMAGEABLE_H
#define ENTITY_DAMAGEABLE_H

#include "gamelogic/entity.h"

#include <iostream>

class DamageableEntity: public Entity {
  protected:
    int health;
  public:
    DamageableEntity(int x, int y, float h, float w, int health): Entity(x, y, h, w), health(health) {
      hitbox = {(int)x, (int)y, (int)h, (int)w};
    };
    void damage(int dp) override {
      health -= dp;
      if (health <= 0 && alive) {
          health = 0;
          onDie();
          return;
      }
    }
    const char* name() override {
      return "DamageableEntity";
    }
    virtual void onDie() {
      alive = false;
    }
    ~DamageableEntity() {};
};

#endif
