#ifndef ENTITY_DROP_H
#define ENTITY_DROP_H

#include "gamelogic/entity.h"
#include "animation.h"
#include "enums.h"
#include "entities_sizes.h"
#include "config.h"

class DropEntity: public Entity {
  private:
    AnimationHandler anim;
    std::string type;
    float time_before_expiry;
    bool dying;
  public:
    DropEntity(float x, float y, uint8_t id, std::string type): Entity(x, y, entities_sizes.at((AnimationState)id).width, entities_sizes.at((AnimationState)id).height),
    anim(id), type(type), time_before_expiry(config.get<float>("game.drop_expiry")), dying(false) {
      hitbox = {(int)x, (int)(y), (int)width, (int)height};
    }

    void applyDeltaV(float dvx, float dvy) override {
      //
    }
    Passability onCollision(Entity& other, Axis axis) override {
      if(this->alive && other.send(type)) {
        this->dying = true;
        this->alive = false;
      }
      return Passability::Transparent;
    }
    const char* name() override {
      return "DropEntity";
    }
    RenderableGameEntity render() override{
      return anim.render(x, y);
    }
    void tick(GameMap& map, float deltaT) override {
      time_before_expiry -= deltaT;
      //if (this->dying) this->alive = false;
      if (time_before_expiry < 0) this->alive = false;
      Entity::tick(map, deltaT);
    }
    ~DropEntity() {};
};

#endif
