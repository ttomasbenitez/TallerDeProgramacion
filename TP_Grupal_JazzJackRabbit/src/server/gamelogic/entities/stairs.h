#ifndef ENTITY_STAIR_H
#define ENTITY_STAIR_H

#include "gamelogic/entity.h"
#include "config.h"
#include "enums.h"
#include "animation.h"
#include "entities_sizes.h"

class Stair : public Entity
{
private:
  float collidedCooldown;
  AnimationHandler anim;
  short direction;
  bool isBeach;

public:
  // Stair(float x, float y, uint8_t id, short direction) : Entity(x, y, entities_sizes.at((AnimationState)id).width, entities_sizes.at((AnimationState)id).height), collidedCooldown(0), direction(direction), anim(id)
  Stair(float x, float y, uint8_t id, short direction, bool isBeach) : Entity(x, y, entities_sizes.at((AnimationState)id).width, entities_sizes.at((AnimationState)id).height), collidedCooldown(0), direction(direction), anim(id), isBeach(isBeach)
  {
    this->applyDeltaV(direction, 0);
    if (isBeach)
    {
      hitbox = {(int)x, (int)(y), (int)width, (int)height};
    }
    else
    {
      hitbox = {(int)x, (int)(y) + (int)height / 8, (int)width, (int)height * 7 / 8};
    }
  };
  const char *name() override
  {
    return "Stair";
  }

  bool isColliding(const Entity &other) const override
  {
    if (this == &other)
      return false;
    // return other.y+other.getHeight()+other.getWidth()/2 > this->y-(height/width) * (other.getX()-this->x)+height;
    Rect otherRect = {(int)other.getX(), (int)other.getY(), (int)other.getWidth(), (int)other.getHeight()};
    return hitbox.Intersects(otherRect);
  }
  virtual Passability onCollision(Entity &other, Axis axis) override
  {
    std::pair<float, float> speed = other.checkSpeed();
    bool c1 = other.getY() + other.getHeight() + other.getWidth() / 2 > this->y - (height / width) * (other.getX() - this->x) + height - 25;
    bool c2 = other.getY() + other.getHeight() + other.getWidth() / 2 > this->y + (height / width) * (other.getX() - this->x) + height - 135;
    if (!isBeach)
    {
      c1 = other.getY() + other.getHeight() + other.getWidth() / 2 > this->y - (height / width) * (other.getX() - this->x) + height - 25;
      c2 = other.getY() + other.getHeight() + other.getWidth() / 2 > this->y + (height / width) * (other.getX() - this->x) + 25;
    }
    if (direction == 1)
    {
      if (c1) // other.getY()< this->y-(height/width) * (other.getX()-this->x)-height for down stairs
      {
        // b stairs.h:43
        if (other.getDirection() == 1)
        {
          if (speed.first != 0)
          {
            other.stopEntityY();
            other.stopEntityX();
            other.applyV(50, 200);
          }
          else
          {
            return Passability::Impassable;
          }
          // other.applyV(200, 200);
        }
        else
        {
          if (speed.first != 0)
          {
            other.stopEntityY();
            other.stopEntityX();
            other.applyDeltaV(0, 0);
          }
          else
          {
            return Passability::Impassable;
          }
        }
        if (axis == Axis::X || axis == Axis::Both)
        {
          return Passability::Impassable;
        }

        return Passability::Passable;
      }
    }
    else if (direction == -1)
    {
      if (c2) // other.getY()< this->y-(height/width) * (other.getX()-this->x)-height for down stairs
      {
        if (other.getDirection() == -1)
        {
          if (speed.first != 0)
          {
            other.stopEntityY();
            other.stopEntityX();
            other.applyV(-50, 200);
          }
          else
          {
            return Passability::Impassable;
          }
        }
        else
        {
          if (speed.first != 0)
          {
            other.stopEntityY();
            other.stopEntityX();
            if (isBeach)
            {
              // other.applyDeltaV(50, -100);
              other.applyDeltaV(0, 0);
            }
            else
            {
              other.applyDeltaV(0, 0);
            }
          }
          else
          {
            return Passability::Impassable;
          }
        }
        // return Passability::Impassable;
      }
    }
    return Passability::Passable;
  }

  void tick(GameMap &map, float deltaT) override
  {
  }
  virtual RenderableGameEntity render() override
  {
    return anim.render(x, y);
  }
  ~Stair(){};
};

#endif
