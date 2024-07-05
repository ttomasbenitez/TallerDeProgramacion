#ifndef ANIMATION_H
#define ANIMATION_H

#include "gamestate.h"
#include "enums.h"
#include "sprites_frames.h"

enum class Animation
{
  Neutral,
  Left,
  LeftFast,
  Right,
  RightFast,
  Jumping,
  Shooting,
  Falling,
  Landing,
  Dying,
  Combo,
  Damage,
  StopShooting,
  Invisible
};

class AnimationHandler
{
private:
  uint8_t entity;
  Animation base;
  Animation current;
  float duration;
  float elapsed;
  int8_t direction;
  bool poisoned;
  int collidedCounter;
  AnimationState getAnimationID(Animation anim)
  {
    switch (this->entity)
    {
    case JAZZ:
    {
      switch (anim)
      {
      case Animation::Neutral:
        return poisoned ? INTOXICATED_IDLE_JAZZ : IDLE_JAZZ;
      case Animation::Left:
      case Animation::Right:
        return poisoned ? INTOXICATED_WALKING_JAZZ : WALKING_JAZZ;
      case Animation::LeftFast:
      case Animation::RightFast:
        return RUNNING_JAZZ;
      case Animation::Jumping:
        return JUMPING_UP_JAZZ;
      case Animation::Shooting:
        return SHOOTING_JAZZ;
      case Animation::Falling:
        return FALLING_JAZZ;
      case Animation::Landing:
        return LANDING_JAZZ;
      case Animation::Dying:
        return DYING_JAZZ;
      case Animation::Combo:
        return UPPERCUT_JAZZ;
      case Animation::Damage:
        return RECEIVE_DAMAGE_JAZZ;
      case Animation::StopShooting:
        return STOP_SHOOTING_JAZZ;
      case Animation::Invisible:
        return DYING_INVISIBLE;
      }
    }
    case LORI:
    {
      switch (anim)
      {
      case Animation::Neutral:
        return poisoned ? INTOXICATED_IDLE_LORI : IDLE_LORI;
      case Animation::Left:
      case Animation::Right:
        return poisoned ? INTOXICATED_WALKING_LORI : WALKING_LORI;
      case Animation::LeftFast:
      case Animation::RightFast:
        return RUNNING_LORI;
      case Animation::Jumping:
        return JUMPING_UP_LORI;
      case Animation::Shooting:
        return SHOOTING_FORWARD_LORI;
      case Animation::Falling:
        return FALLING_LORI;
      case Animation::Landing:
        return LANDING_LORI;
      case Animation::Combo:
        return FLYING_KICK_LORI;
      case Animation::Damage:
        return RECEIVE_DAMAGE_LORI;
      case Animation::StopShooting:
        return STOP_SHOOTING_FORWARD_LORI;
      case Animation::Dying:
        return DYING_LORI;
      case Animation::Invisible:
        return DYING_INVISIBLE;
      }
    }
    case SPAZ:
    {
      switch (anim)
      {
      case Animation::Neutral:
        return poisoned ? INTOXICATED_IDLE_SPAZ : IDLE_SPAZ;
      case Animation::Left:
      case Animation::Right:
        return poisoned ? INTOXICATED_WALKING_SPAZ : WALKING_SPAZ;
      case Animation::LeftFast:
      case Animation::RightFast:
        return RUNNING_SPAZ;
      case Animation::Jumping:
        return JUMPING_UP_SPAZ;
      case Animation::Shooting:
        return SHOOTING_FORWARD_SPAZ;
      case Animation::Falling:
        return FALLING_SPAZ;
      case Animation::Landing:
        return LANDING_SPAZ;
      case Animation::Combo:
        return FLYING_KICK_SPAZ;
      case Animation::Damage:
        return RECEIVE_DAMAGE_SPAZ;
      case Animation::StopShooting:
        return STOP_SHOOTING_FORWARD_SPAZ;
      case Animation::Dying:
        return DYING_SPAZ;
      case Animation::Invisible:
        return DYING_INVISIBLE;
      }
    }
    default:
    {
      if (anim == Animation::Dying)
        return DYING_INVISIBLE;
      return (AnimationState)entity;
    }
    }
    return Background2;
  }
  uint8_t getAnimationFrame()
  {
    // if (this->isBusy()) return 0;
    return uint8_t(elapsed);
  }

public:
  AnimationHandler(uint8_t entity) : entity(entity), base(Animation::Neutral), current(Animation::Neutral), duration(animations_frames.at(getAnimationID(this->base)).size()), elapsed(0), direction(1), poisoned(false) {}
  RenderableGameEntity render(float x, float y)
  {
    return RenderableGameEntity{
        x, y,
        (uint8_t)entity,
        (uint8_t)getAnimationID(this->base), // this->isBusy() ? this->current :
        (uint8_t)getAnimationFrame(),
        direction};
  }
  void tick(float deltaT)
  {
    if ((base == Animation::Dying || base == Animation::StopShooting) && this->isFinished())
    {
      return;
    }
    this->elapsed += 1;
    if (elapsed >= duration)
    {
      if (base == Animation::Combo || base == Animation::Landing || base == Animation::Damage)
      {
        setBase(Animation::Neutral);
      }
      elapsed = 0;
    }
  }
  void setBase(Animation anim)
  {
    if ((base == Animation::Combo) && isBusy())
    {
      return;
    }
    switch (anim)
    {
    case Animation::Left:
      if (base == Animation::LeftFast)
        return;
      break;
    case Animation::Right:
      if (base == Animation::RightFast)
        return;
      break;
    default:
      break;
    }
    if (anim == base)
    {
      return;
    }
    if (!animations_frames.count(getAnimationID(anim)))
    {
      this->duration = 0;
    }
    else
    {
      this->base = anim;
      this->duration = animations_frames.at(getAnimationID(this->base)).size();
      this->elapsed = 0;
    }
    if (anim == Animation::Left || anim == Animation::LeftFast)
      direction = -1;
    if (anim == Animation::Right || anim == Animation::RightFast)
      direction = +1;
  }
  void restoreFromPoison()
  {
      poisoned = false;
      this->base = Animation::Neutral;
      this->duration = animations_frames.at(getAnimationID(this->base)).size();
      this->elapsed = 0;
  }
  bool isBusy()
  {
    return duration > elapsed + 1;
  }
  void animate(Animation anim, float duration)
  {
    this->current = anim;
    this->duration = duration;
    this->elapsed = 0;
  }
  void setPoisoned(bool val)
  {
    poisoned = val;
  }
  int8_t getDirection()
  {
    return direction;
  }
  bool isFinished()
  {
    return elapsed + 1 == duration;
  }
  void flip()
  {
    direction = direction * -1;
  }
  Animation getState()
  {
    return base;
  }
};

#endif
