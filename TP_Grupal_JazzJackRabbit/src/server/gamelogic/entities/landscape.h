#ifndef ENTITY_LANDSCAPE_H
#define ENTITY_LANDSCAPE_H

#include "gamelogic/entity.h"
#include "config.h"
#include "enums.h"
#include "animation.h"
#include "entities_sizes.h"

class Landscape: public Entity {
  private:
    float collidedCooldown;
    AnimationHandler anim;
    short direction;
  public:
    Landscape(float x, float y, uint8_t id): Entity(x, y, entities_sizes.at((AnimationState)id).width, entities_sizes.at((AnimationState)id).height), collidedCooldown(0), direction(+1), anim(id) {
      this->applyDeltaV(direction, 0);
      hitbox = {(int)x, (int)(y+height/2), (int)1, 1};
    };
    const char* name() override {
      return "Landscape";
    }
    virtual Passability onCollision(Entity& other, Axis axis) override {
      return Passability::Passable;
    }
    void tick(GameMap& map, float deltaT) override {
    }
    virtual RenderableGameEntity render() override{
      return anim.render(x, y);
    }
    ~Landscape() {};
};

#endif
