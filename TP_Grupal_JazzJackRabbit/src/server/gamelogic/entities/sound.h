#ifndef SOUND_H
#define SOUND_H

#include "../entity.h"
#include "enums.h"

class SoundEntity : public Entity {
private:
    int ticks;
    AnimationState soundType;
public:
    explicit SoundEntity(AnimationState type): Entity(0, 0, 0, 0), ticks(0), soundType(type) {}

    static std::unique_ptr<SoundEntity> create(AnimationState type) {
        return std::make_unique<SoundEntity>(type);
    }

    const char* name() override {
        return "Sound";
    }

    void tick(GameMap& map, float deltaT) override {
        if (ticks > 0) {
            this->alive = false;
            return;
        }
        ticks++;
    }

    virtual RenderableGameEntity render() override{
        return RenderableGameEntity {
                x,
                y,
                soundType,
                soundType,
                1,
                direction
        };
    }
    ~SoundEntity() {};
};

#endif //SOUND_H
