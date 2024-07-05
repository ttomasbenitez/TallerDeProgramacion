#ifndef ENTITY_EDGES_H
#define ENTITY_EDGES_H

#include "gamelogic/entity.h"

class EdgesEntity : public Entity
{
private:
  float width;
  float height;

public:
  EdgesEntity(float width, float height, float x, float y) : Entity(x, y, 0, 0), width(width), height(height){};
  bool isColliding(const Entity &other) const override
  {
    if (this == &other)
      return false;
    if (other.getX() < x)
      return true;
    if (other.getX() + other.getWidth() > width)
      return true;
    return false;
  }
  Passability onCollision(Entity &other, Axis axis) override
  {
    return Passability::Impassable;
  }
  void tick(GameMap &map, float deltaT) override
  {
    map.map([&](int id, Entity &other)
            {
        if (this->isColliding(other)) other.damage(1); });
  }
  void damage(int dp) override
  {
    // indestructible
  }
  bool tryMove(float x, float y, GameMap &others) override
  {
    // immovable
    return false;
  }
  void applyDeltaV(float dvx, float dvy) override
  {
    // immovable
  }
  const char *name() override
  {
    return "Edges";
  }
  ~EdgesEntity(){};
};

#endif
