#ifndef ENTITY_SPAWNER_H
#define ENTITY_SPAWNER_H

#include "gamelogic/entity.h"

template<typename T>
class SpawnerEntity: public Entity {
  private:
    float cooldown;
    int id;
  public:
    SpawnerEntity(float x, float y): Entity(x, y, 0, 0), cooldown(0), id(-1);
    const char* name() override {
      return "SpawnerEntity";
    }
    Passability onCollision(Entity& other, Axis axis) override {
      return Passability::Transparent;
    }
    void tick(GameMap& map, float deltaT) override {
      cooldown -= deltaT;
      if (!map.isAlive(id)) {
        if (cooldown <= 0) {
          auto& entity = std::make_unique<T>(x, y);
          map.add(std::move(entity));
          cooldown = config.get<float>("game.enemy_respawn_cooldown");
        }
      }
    }
    void applyDeltaV(float dvx, float dvy) override {
      // stationary
    }
    ~SpawnerEntity() {};
};

#endif
