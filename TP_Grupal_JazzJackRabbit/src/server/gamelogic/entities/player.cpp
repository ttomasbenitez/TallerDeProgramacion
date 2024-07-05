#include "player.h"
#include "config.h"
#include "bullet.h"
#include "gamelogic/gamemap.h"
#include <memory>
#define PROJECTILE_SPEED config.get<int>("game.base_projectile_speed")
#define BULLET_DAMAGE config.get<int>("game.base_weapon_damage")
#define FIREBALL_DAMAGE config.get<int>("game.fireball_weapon_damage")
#define ROCKET_DAMAGE config.get<int>("game.rocket_weapon_damage")
#define COMBO_DAMAGE config.get<int>("game.combo_damage")
#define SHOOTING_SPEED config.get<int>("game.base_shooting_speed")
#define DEFAULT_GUN Gun(-1, SHOOTING_SPEED, PROJECTILE_SPEED, BULLET_DAMAGE, -1, BULLET, BULLET_SOUND)
#define ROCKET_GUN Gun(0, SHOOTING_SPEED, PROJECTILE_SPEED * 2, ROCKET_DAMAGE, 5, SHOT_RED_ROCKET, RED_ROCKET_SOUND)
#define FIREBALL_GUN Gun(0, SHOOTING_SPEED * 3, PROJECTILE_SPEED, FIREBALL_DAMAGE, 10, SHOT_FIREBALL, FIREBALL_SOUND)

PlayerEntity::PlayerEntity(float x, float y, int id, int health, std::string player_name, GameMap &map, int characterID) : DamageableEntity(x, y, 78, 40, health),
                                                                                                                           id(id),
                                                                                                                           anim((AnimationState)characterID),
                                                                                                                           map(map),
                                                                                                                           revive_cooldown(0),
                                                                                                                           poisoned(false),
                                                                                                                           poisoned_cooldown(0),
                                                                                                                           player_name(player_name),
                                                                                                                           guns{DEFAULT_GUN, ROCKET_GUN, FIREBALL_GUN},
                                                                                                                           currentGun(0)
{
}

const char *PlayerEntity::name()
{
  return "PlayerEntity";
}

bool PlayerEntity::send(const std::string &cmd)
{
  if ((anim.getState() == Animation::Damage) && anim.isBusy())
  {
    vx=0;
    vy=0;
   return false;
  }
  if (cmd == "revive")
  {
    health = 0;
    alive = true;
    this->revive_cooldown = config.get<float>("game.player_respawn_cooldown");
  }
  if (this->health <= 0)
    return false;
  if (cmd == "stop_moving")
  {
    this->vx = 0;
    if (anim.getState() == Animation::Falling)
    {
      return true;
    }
    anim.setBase(Animation::Neutral);
    return true;
  }
  if (cmd == "stop_shooting" && !poisoned)
  {
    
    anim.setBase(Animation::StopShooting);
    return true;
  }
  if (cmd == "left")
  {
    if (anim.getState() == Animation::LeftFast)
    {
      return true;
    }
    float dx = -config.get<float>("physics.player_speed");
    if (poisoned)
      dx *= -1;
    // this->applyDeltaV(dx, 0);
    if (vx > 0)
    {
      this->vx = 0;
    }
    else
    {
      this->vx = dx;
    }
    direction = -1;
    anim.setBase(Animation::Left);
    return true;
  }
  if (cmd == "left_fast" && !poisoned)
  {
    this->vx = -config.get<float>("physics.player_speed_fast");
    direction = -1;
    anim.setBase(Animation::LeftFast);
    return true;
  }
  if (cmd == "right")
  {
    if (anim.getState() == Animation::RightFast)
    {
      return true;
    }
    float dx = +config.get<float>("physics.player_speed");
    if (poisoned)
      dx *= -1;
    // this->applyDeltaV(dx, 0);
    if (vx < 0)
    {
      this->vx = 0;
    }
    else
    {
      this->vx = dx;
    }
    direction = 1;
    anim.setBase(Animation::Right);
    return true;
  }
  if (cmd == "right_fast" && !poisoned)
  {
    // this->applyDeltaV(+config.get<float>("physics.player_speed_fast"), 0);
    this->vx = +config.get<float>("physics.player_speed_fast");
    direction = 1;
    anim.setBase(Animation::RightFast);
    return true;
  }
  if (cmd == "jump" && !poisoned)
  {
    if ((int)vy != 0)
    {
      return true;
    }

    this->applyDeltaV(0, +config.get<float>("physics.jump_speed"));
    anim.setBase(Animation::Jumping);
    return true;
  }
  if (cmd == "shoot" && !poisoned)
  {
    anim.setBase(Animation::Shooting);
    if (guns[currentGun].hasAmmunition() && guns[currentGun].canShoot())
    {
      map.add(SoundEntity::create(guns[currentGun].getSoundType()));

      if (anim.getDirection() > 0)
      {
        auto bullet = guns[currentGun].shoot(x + width/3, y+height/3, +1);
        map.add(std::move(bullet));
      }
      else
      {
        auto bullet = guns[currentGun].shoot(x, y+height/3, -1);
        map.add(std::move(bullet));
      }
      
    }
    return true;
  }
  if (cmd == "coin" || cmd == "gem")
  {
    this->points += config.get<float>("game.coin_points");
    map.add(SoundEntity::create(COIN_SOUND));
    return true;
  }
  if (cmd == "poison")
  {
      map.add(SoundEntity::create(POISONED_SOUND));
      poisoned = true;
    poisoned_cooldown = config.get<float>("game.poison_time");
    anim.setPoisoned(true);
    return true;
  }
  if (cmd == "switch_gun")
  {
    (this->currentGun == (guns.size()) - 1) ? currentGun = 0 : ++currentGun;
    while (guns[currentGun].hasAmmunition() == false)
    {
      (this->currentGun == (guns.size()) - 1) ? currentGun = 0 : ++currentGun;
    }
    anim.setBase(Animation::Neutral);
    return true;
  }
  if (cmd == "full_ammo")
  {
    for (Gun& gun: guns)
    {
      gun.addAmmunition(gun.magSize());
    }
    return true;
  }
  if (cmd == "fireball")
  {
    guns[2].addAmmunition(2);
    return true;
  }
  if (cmd == "rocket")
  {
    guns[1].addAmmunition(2);
    return true;
  }
  else
  {
    anim.setBase(Animation::Neutral);
  }
  if (cmd == "combo" && !poisoned)
  {
     if ((int)vy != 0)
    {
      return true;
    }
    switch (anim.render(1, 1).entity)
    {
    case JAZZ: 
    this->applyDeltaV(0, +config.get<float>("physics.jump_speed"));
    break;
    case LORI:
    this->applyDeltaV(0, +config.get<float>("physics.jump_speed")/2);
      break;
    case SPAZ:
    this->applyDeltaV(direction * config.get<float>("physics.player_speed_fast")*2, +config.get<float>("physics.jump_speed")/2); 
    default:
      break;
    }
    anim.setBase(Animation::Combo);
    return true;
  }
  return false;
}

bool PlayerEntity::isPlayer(){
  return true;
}

void PlayerEntity::tick(GameMap &map, float deltaT)
{
  if ((anim.getState() == Animation::Damage)&& anim.isBusy())
  {
    vy = 0;
    this->anim.tick(deltaT);
    return;
  }
  DamageableEntity::tick(map, deltaT);
  for (Gun &gun : guns)
  {
    gun.tick();
  }
  this->anim.tick(deltaT);
  this->revive_cooldown -= deltaT;
  this->poisoned_cooldown -= deltaT;
  if (this->revive_cooldown > 0 )
  {
    anim.setBase(Animation::Dying);
    return;
  }
  if (this->revive_cooldown <= 0 && this->health == 0)
  {
    anim.setBase(Animation::Neutral);
    health = config.get<int>("game.player_health");
  }
  if (poisoned && this->poisoned_cooldown <= 0 && anim.isFinished())
  {
    poisoned = false;
    anim.restoreFromPoison();
  }
  // this->vy = 0;
  if (this->vy > 1)
  {
    anim.setBase(Animation::Falling);
  }
  if ((int)this->vy == 0 && anim.getState() == Animation::Falling)
  {
    map.add(SoundEntity::create(LANDING_SOUND));
    anim.setBase(Animation::Landing);
  }
  if (anim.getState() == Animation::StopShooting && anim.isFinished())
  {
    anim.setBase(Animation::Neutral);
  }
}

Passability PlayerEntity::onCollision(Entity& other, Axis axis) {
  if(anim.getState() == Animation::Combo){
    other.damage(COMBO_DAMAGE);
  }
  return Passability::Passable;
}

std::optional<Player> PlayerEntity::asPlayer()
{
  return Player{
      id,
      (uint8_t)this->health,
      (uint16_t)points,
      this->anim.render(x, y),
      player_name,
      guns[currentGun].getType(),
      (int8_t)guns[currentGun].currentAmmo()};
}


void PlayerEntity::damage(int dp) {
  health -= dp;
  if (health <= 0 && alive) {
        health = 0;
        onDie();
        return;
    }
  map.add(SoundEntity::create(HURT_SOUND));
  anim.setBase(Animation::Damage);
}


void PlayerEntity::onDie()
{
  map.add(SoundEntity::create(DYING_SOUND));
  vy = 0;
  vx=0;
  alive = false;
  //DamageableEntity::onDie();
}