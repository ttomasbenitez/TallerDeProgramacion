#ifndef ENTITY_FLOATINGPLATFORM_H
#define ENTITY_FLOATINGPLATFORM_H

#include "gamelogic/entity.h"
#include "config.h"
#include "enums.h"
#include "animation.h"
#include "entities_sizes.h"

class FloatingPlatform: public Entity {
  private:
    float collidedCooldown;
    AnimationHandler anim;
    short direction;
  public:
    FloatingPlatform(float x, float y, uint8_t id): Entity(x, y, entities_sizes.at((AnimationState)id).width, entities_sizes.at((AnimationState)id).height), collidedCooldown(0), direction(+1), anim(id) {
      this->applyDeltaV(direction, 0);
      hitbox = {(int)x, (int)(y), (int)width, 1};
    };
    const char* name() override {
      return "FloatingPlatform";
    }
    virtual Passability onCollision(Entity& other, Axis axis) override {

        if (axis == Axis::Y)
        {
            //other.y = this->y;
            //other.stopEntityY();
            return Passability::Impassable;
        }
      return Passability::Passable;
    }
    void tick(GameMap& map, float deltaT) override {
    }
    virtual RenderableGameEntity render() override{
      return anim.render(x, y);
    }
    ~FloatingPlatform() {};
};

#endif
