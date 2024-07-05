#include "entity.h"
#include "gamemap.h"
#include "config.h"
#include "enums.h"
#include "entities/player.h"
#include "entities/tall_platform.h"

#include <algorithm>
#include <list>

Entity::Entity(float x, float y, float width, float height) : vx(0), vy(0), alive(true),
                                                              x(x), y(y), width(width), height(height), direction(+1) {}

bool Entity::isPlayer()
{
  return false;
}

void Entity::applyDeltaV(float dvx, float dvy)
{
  this->vx += dvx;
  this->vy -= dvy;
}

void Entity::applyV(float dvx, float dvy)
{
  this->vx = dvx;
  this->vy = -dvy;
}

void Entity::stopEntityY()
{
  this->vy = 0;
}

void Entity::stopEntityX()
{
  this->vx = 0;
}
float Entity::getX() const
{
  return x;
}
float Entity::getY() const
{
  return y;
}
float Entity::getWidth() const
{
  return width;
}
int Entity::getHitboxHeight() const
{
  return hitbox.GetH();
}
float Entity::getHeight() const
{
  return height;
}
void Entity::setX(float x)
{
  this->x = x;
}
void Entity::setY(float y)
{
  this->y = y;
}

int8_t Entity::getDirection() const
{
  return direction;
}

bool Entity::isColliding(const Entity &other) const
{
  if (this == &other)
    return false;
  Rect otherRect = {(int)other.x, (int)other.y, (int)other.width, (int)other.height};
  return hitbox.Intersects(otherRect);
  if (other.x >= this->x + this->width)
    return false;
  if (this->x >= other.x + other.width)
    return false;
  if (other.y >= this->y + this->height)
    return false;
  if (this->y >= other.y + other.height)
    return false;
  return true;
}

#include <cstdio>

bool Entity::tryMove(float x, float y, GameMap &map)
{
  float oldx = this->x, oldy = this->y;
  this->x = x;
  this->y = y;
  bool valid = true;
  Axis axis;
  if (x == oldx && y == oldy)
    return true;
  if (x != oldx)
    axis = Axis::X;
  if (y != oldy)
    axis = Axis::Y;
  if (x != oldx && y != oldy)
    axis = Axis::Both;
  map.map([&](int id, Entity &other)
          {
    if (other.isColliding(*this)) {
      Passability this_passability = this->onCollision(other, axis);
      Passability other_passability = other.onCollision(*this, axis);
      if (this_passability == Passability::Impassable || other_passability == Passability::Impassable) {
        valid = false;
      }
      if (this_passability == Passability::Passable && other_passability == Passability::Passable) {
        if (valid==false)
        {
          return;
        }
        valid = true;
      }
    } });
  if (!valid)
  {
    this->x = oldx;
    this->y = oldy;
  }
  return valid;
}

#include <iostream>

void Entity::tick(GameMap &map, float deltaT)
{

  if (this->isDead())
    return;
  int tries = 100;
  while (!this->tryMove(x + vx * deltaT, y, map) && tries-- > 0)
  {
    vx /= config.get<float>("physics.impact_speed_reduction_factor");
  }
  while (!this->tryMove(x, y + vy * deltaT, map) && tries-- > 0)
  {
    vy /= config.get<float>("physics.impact_speed_reduction_factor");
  }
  hitbox.SetX(x);
  hitbox.SetY(y);
}

void Entity::damage(int dp)
{
  // take no damage
}

bool Entity::isDead() const
{
  return !alive;
}

Passability Entity::onCollision(Entity &other, Axis axis)
{
  return Passability::Passable;
}

std::pair<float, float> Entity::checkSpeed()
{
  return {vx, vy};
}

RenderableGameEntity Entity::render()
{
  return RenderableGameEntity{
      x,
      y,
      JAZZ,
      DYING_INVISIBLE,
      0,
      direction};
}

std::optional<Player> Entity::asPlayer()
{
  return std::nullopt;
}

bool Entity::send(const std::string &cmd)
{
  // do nothing
  return false;
}
