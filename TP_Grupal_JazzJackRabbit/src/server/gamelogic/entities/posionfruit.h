#ifndef ENTITY_POISONFRUIT_H
#define ENTITY_POISONFRUIT_H

#include "../entity.h"
#include "animation.h"


class PoisonedFruitEntity: public Entity {
private:
    AnimationHandler anim;
    bool dying;
public:
    PoisonedFruitEntity(float x, float y, uint8_t id): Entity(x, y, entities_sizes.at((AnimationState)id).width, entities_sizes.at((AnimationState)id).height), anim(id), dying(false) {
        hitbox = {(int)x, (int)(y), (int)width, (int)height};
    };

    void applyDeltaV(float dvx, float dvy) override {
      // 
    }
    Passability onCollision(Entity& other, Axis axis) override {
        if(!this->dying && other.isPlayer()) {
            this->dying  = true;
            this->anim.setBase(Animation::Dying);
            other.send("poison");
        }
        return Passability::Transparent;
    }
    void tick(GameMap& map, float deltaT) override {
        if (this->dying) {
            this->alive = false;
        }
        if (!this->alive) return;
        Entity::tick(map, deltaT);
    }
    const char* name() override {
      return "PoisonedFruitEntity";
    }
    virtual RenderableGameEntity render() override {
        return anim.render(x, y);
    }

    ~PoisonedFruitEntity() {};
};

#endif
