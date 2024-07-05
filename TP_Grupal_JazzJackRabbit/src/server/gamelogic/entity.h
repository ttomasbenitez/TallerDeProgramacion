#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <optional>

#include "gamestate.h"
#include <SDL2pp/SDL2pp.hh>
using namespace SDL2pp;

class GameMap;

enum class Passability
{
  Transparent, // Other objects may go over it
  Passable,    // May go over other objects
  Impassable   // Can never be traversed
};

enum class Axis
{
  X,
  Y,
  Both
};

class Entity
{
protected:
  float vx;
  float vy;
  bool alive;
  float x;
  float y;
  Rect hitbox;
  float width;
  float height;
  int8_t direction;

public:
  explicit Entity(float x, float y, float width, float height);
  bool isDead() const;

  void stopEntityY();
  void stopEntityX();
  float getX() const;
  float getY() const;
  float getWidth() const;
  int getHitboxHeight() const;
  float getHeight() const;
  int8_t getDirection() const;
  void setX(float x);
  void setY(float y);
  virtual const char *name()
  {
    return "Entity";
  };
  virtual bool isPlayer();
  virtual void applyDeltaV(float dvx, float dvy);
  virtual bool isColliding(const Entity &other) const;
  virtual void tick(GameMap &map, float deltaT);
  virtual void damage(int dp);
  virtual Passability onCollision(Entity &other, Axis axis);
  virtual bool tryMove(float x, float y, GameMap &map);
  virtual RenderableGameEntity render();
  virtual std::optional<Player> asPlayer();
  virtual bool send(const std::string &cmd);
  virtual std::pair<float, float> checkSpeed();
  virtual void applyV(float dvx, float dvy);
  virtual ~Entity(){};

  Entity(const Entity &) = delete;
  Entity &operator=(const Entity &) = delete;

  Entity(Entity &&other) = delete;
  Entity &operator=(Entity &&other) = delete;
};

#endif
