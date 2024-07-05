#ifndef ENTITY_SPIKES_H
#define ENTITY_SPIKES_H

#include "gamelogic/entity.h"
#include "animation.h"
#include "enums.h"

class SpikesEntity: public Entity {
  private:
    float cooldown;
    bool didDamage;
  public:
    SpikesEntity(float x, float y): Entity(x, y, 1, 1), cooldown(0), didDamage(false) {};
    const char* name() override {
      return "SpikesEntity";
    }
    Passability onCollision(Entity& other, Axis axis) override {
      if (cooldown <= 0) {
        didDamage = true;
        other.damage(1);
      }
      return Passability::Transparent;
    }
    void tick(GameMap& map, float deltaT) override {
      cooldown -= deltaT;
      Entity::tick(map, deltaT);
      if (didDamage) {
        cooldown = 1;
        didDamage = false;
      }
    }
    void applyDeltaV(float dvx, float dvy) override {
      // stationary
    }
    virtual RenderableGameEntity render() override{
       return RenderableGameEntity {
          x,
          y,
          0,
          BEACH_PLATFORM,
          0,
          direction
        };
    }
    ~SpikesEntity() {};
};

#endif
