#ifndef ENTITY_PLATFORM_H
#define ENTITY_PLATFORM_H

#include "gamelogic/entity.h"
#include "config.h"
#include "enums.h"
#include "animation.h"
#include "entities_sizes.h"

class Platform: public Entity {
  private:
    float collidedCooldown;
    AnimationHandler anim;
    short direction;
  public:
    Platform(float x, float y, uint8_t id): Entity(x, y, entities_sizes.at((AnimationState)id).width, entities_sizes.at((AnimationState)id).height), collidedCooldown(0), direction(+1), anim(id) {
      this->applyDeltaV(direction, 0);
      hitbox = {(int)x, (int)(y), (int)width, (int)height};
    };
    const char* name() override {
      return "Platform";
    }
    virtual Passability onCollision(Entity& other, Axis axis) override {
      //if(axis == Axis::X) return Passability::Passable;
      return Passability::Impassable;
    }
    void tick(GameMap& map, float deltaT) override {
    }
    virtual RenderableGameEntity render() override{
      return anim.render(x, y);
    }
    ~Platform() {};
};

#endif
