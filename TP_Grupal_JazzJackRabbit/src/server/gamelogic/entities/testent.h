#ifndef ENTITY_TESTENT_H
#define ENTITY_TESTENT_H

#include "gamelogic/entities/damageable.h"

class TestEntity: public DamageableEntity {
  public:
    TestEntity(float x, float y, int health): DamageableEntity(x, y, 10, 10, health) {};
    const char* name() override {
      return "TestEntity";
    }
    ~TestEntity() {};
};

#endif
