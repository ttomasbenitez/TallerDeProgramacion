#ifndef ENTITY_HPLATFORM_H
#define ENTITY_HPLATFORM_H

#include "gamelogic/entity.h"

class HPlatformEntity: public Entity {
  private:
    float collidedCooldown;
    short direction;
  public:
    HPlatformEntity(float x, float y): Entity(x, y, 2, 1), collidedCooldown(0), direction(+1) {
      this->applyDeltaV(direction, 0);
    };
    const char* name() override {
      return "HPlatformEntity";
    }
    virtual Passability onCollision(Entity& other, Axis axis) override {
      if (axis != Axis::Y && collidedCooldown <= 0) {
        collidedCooldown = 1;
        direction = -direction;
      }
      return Passability::Passable;
    }
    void tick(GameMap& map, float deltaT) override {
      collidedCooldown -= deltaT;
      this->vx = direction;
      Entity::tick(map, deltaT);
    }
    ~HPlatformEntity() {};
};

#endif
