#ifndef ENTITY_BULLET_H
#define ENTITY_BULLET_H

#include "gamelogic/entity.h"
#include "enums.h"
#include "damageable.h"
#include "coin.h"
#include "drop.h"
#include "stairs.h"
#include "posionfruit.h"

class BulletEntity: public Entity {
  private:
    int dp;
    AnimationState bulletType;
    int speedModifier;
  public:
    BulletEntity(float x, float y, float vx, int damage, AnimationState type): Entity(x, y, 10, 10), dp(damage), bulletType(type){
      this->applyDeltaV(vx, 0);
    };
    void applyDeltaV(float dvx, float dvy) override {
      this->vx += dvx;
      // no vy
    }
    Passability onCollision(Entity& other, Axis axis) override {
      auto *coinEntity = dynamic_cast<CoinEntity *>(&other);
      auto *dropEntity = dynamic_cast<DropEntity *>(&other);
      auto *poisonEntity = dynamic_cast<PoisonedFruitEntity *>(&other);


        if (coinEntity||dropEntity||poisonEntity)
      {
        return Passability::Transparent;
      }
      if (!other.isPlayer())
      {
          /*if (!(other.onCollision(*this, axis) == Passability::Passable))
          {
              this->alive = false;
              other.damage(dp);
          }*/
          this->alive = false;
          other.damage(dp);
      }
      return Passability::Transparent;
    }
    void damage(int dp) override {
      this->alive = false;
    }
    const char* name() override {
      return "Bullet";
    }
    virtual RenderableGameEntity render() override{
       return RenderableGameEntity {
          x,
          y,
          bulletType,
          bulletType,
          1,
          direction
        };
    }
    ~BulletEntity() {};
};

#endif
