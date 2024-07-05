#ifndef ENTITY_WANDERING_H
#define ENTITY_WANDERING_H

#include "gamelogic/entities/damageable.h"
#include "gamelogic/entities/drop.h"
#include "gamelogic/entities/player.h"

#include "config.h"
#include "enums.h"
#include "animation.h"

#include <random>
#include <unordered_map>

class WanderingEntity : public DamageableEntity
{
private:
  float collidedCooldown;
  AnimationHandler anim;
  bool dying;
  int timer;
  float spawnX;
  float spawnY;
  bool despawned;
  int counter;
  int damage;
  int base_health;
private:
  uint8_t getDropId(std::string drop)
  {
    if (drop == "gem")
      return AnimationState::GEM;
    if (drop == "rocket")
      return AnimationState::RED_ROCKET;
    if (drop == "fireball")
      return AnimationState::FIREBALL;
    throw std::runtime_error("Unknown drop type.");
  }

public:
  WanderingEntity(float x, float y, uint8_t id) : DamageableEntity(x, y, entities_sizes.at((AnimationState)id).width, entities_sizes.at((AnimationState)id).height, 0), collidedCooldown(0), anim(id), dying(false), counter(0)
  {
    this->applyDeltaV(direction, 0);
    anim.setBase(Animation::Right);
    spawnX = x;
    spawnY = y;
    despawned = false;

    switch (id) {
       case CRAB:
           damage = config.get<int>("entities.crab.damage");
           health = config.get<int>("entities.crab.health");
           break;
       case FISH:
           damage = config.get<int>("entities.fish.damage");
           health = config.get<int>("entities.fish.health");
           break;
       case TURTLE:
           damage = config.get<int>("entities.turtle.damage");
           health = config.get<int>("entities.turtle.health");
           break;
       case MAD_HATTER:
          damage = config.get<int>("entities.madHatter.damage");
          health = config.get<int>("entities.madHatter.health");
          break;
       case SKELETON:
          damage = config.get<int>("entities.skeleton.damage");
          health = config.get<int>("entities.skeleton.health");
          break;
       default:
           damage = 0;
           health = 0;
           break;
      }
      base_health = health;

  };
  const char *name() override
  {
    return "WanderingEntity";
  }
  virtual Passability onCollision(Entity &other, Axis axis) override
  {
    PlayerEntity *playableEntity = dynamic_cast<PlayerEntity *>(&other);

    if ((despawned) || !playableEntity || collidedCooldown >= 0)
    {
      return Passability::Passable;
    }
    if (axis != Axis::Y && !playableEntity)
    {
      direction = -direction;
    }
    if (/*axis != Axis::Y &&*/ collidedCooldown <= 0 && playableEntity)
    {
      collidedCooldown = 1;
      other.damage(damage);

    }
    return Passability::Impassable;
  }
  void tick(GameMap &map, float deltaT) override
  {
    if (dying)
    {
      static std::default_random_engine e;
      static std::uniform_real_distribution<> dis(0, 1);
      const auto &drops = config.get<std::unordered_map<std::string, float>>("entities.wandering.drops");
      for (const auto &[drop, prob] : drops)
      {
        float random = dis(e);
        if (random > prob)
          continue;
        auto dropped = std::make_unique<DropEntity>(x, y, getDropId(drop), drop);
        map.add(std::move(dropped));
        break;
      }
      map.add(SoundEntity::create(DYING_ENEMY_SOUND));
      this->dying = false;
      // this->alive = false;
      this->despawned = true;
      x = 0;
      y = 0;
      hitbox.SetX(x);
      hitbox.SetY(y);
    }
    if (this->despawned)
    {
      timer++;
      if (timer == (config.get<int>("game.enemy_respawn_cooldown") * 15))
      {
        timer = 0;
        this->despawned = false;
        this->alive = true;
        anim.setBase(Animation::Neutral);
        x = spawnX;
        y = spawnY;
        health = base_health;
        vy = 0;
      }
      return;
    }
    ++counter;
    if (counter == config.get<int>("physics.tps")*3)
    {
      direction = direction * -1;
      anim.flip();
      counter =0;
    }
    collidedCooldown -= deltaT;
    this->vx = direction * config.get<float>("physics.player_speed")/3;
    DamageableEntity::tick(map, deltaT);
    anim.tick(deltaT);
  }
  virtual RenderableGameEntity render() override
  {
    return anim.render(x, y);
  }
  void onDie() override
  {
    if (this->despawned)
    {
      return;
    }
    this->dying = true;
    timer = 0;
    anim.setBase(Animation::Dying);
  }

  ~WanderingEntity(){};
};

#endif
