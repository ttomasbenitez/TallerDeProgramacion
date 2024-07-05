#ifndef ENTITY_TALL_PLATFORM_H
#define ENTITY_TALL_PLATFORM_H

#include "gamelogic/entity.h"
#include "config.h"
#include "enums.h"
#include "animation.h"
#include "entities_sizes.h"

class TallPlatform : public Entity
{
private:
  float collidedCooldown;
  AnimationHandler anim;
  short direction;

public:
  TallPlatform(float x, float y, uint8_t id, bool isStoneTowerFloor) : Entity(x, y, entities_sizes.at((AnimationState)id).width, entities_sizes.at((AnimationState)id).height), collidedCooldown(0), direction(+1), anim(id)
  {
    this->applyDeltaV(direction, 0);
    if (isStoneTowerFloor)
    {
      hitbox = {(int)x, (int)(y) + (int)height / 2, (int)width, (int)height * 1 / 2};
    }
    else
    {
      hitbox = {(int)x, (int)(y) + (int)height / 4, (int)width, (int)height * 3 / 4};
    }
  };
  const char *name() override
  {
    return "TallPlatform";
  }
  virtual Passability onCollision(Entity &other, Axis axis) override
  {
    return Passability::Impassable;
  }
  void tick(GameMap &map, float deltaT) override
  {
  }
  virtual RenderableGameEntity render() override
  {
    return anim.render(x, y);
  }
  ~TallPlatform(){};
};

#endif
