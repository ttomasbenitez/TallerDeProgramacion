#ifndef ENTITY_STATIC_H
#define ENTITY_STATIC_H

#include "gamelogic/entity.h"
#include "config.h"
#include "enums.h"
#include "animation.h"

class Static: public Entity {
  private:
    float collidedCooldown;
    AnimationHandler anim;
    short direction;
  public:
    Static(float x, float y, uint8_t id): Entity(x, y, 2, 1), collidedCooldown(0), direction(+1), anim(id) {
      this->applyDeltaV(direction, 0);
    };
    const char* name() override {
      return "Static";
    }
    virtual Passability onCollision(Entity& other, Axis axis) override {
      return Passability::Passable;
    }
    void tick(GameMap& map, float deltaT) override {
    }
    virtual RenderableGameEntity render() override{
      return anim.render(x, y);
    }
    ~Static() {};
};

#endif
