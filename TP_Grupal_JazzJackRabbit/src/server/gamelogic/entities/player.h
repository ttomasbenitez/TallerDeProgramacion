#ifndef ENTITY_PLAYER_H
#define ENTITY_PLAYER_H

#include "damageable.h"
#include "animation.h"
#include "gun.h"
#include "sound.h"

class PlayerEntity: public DamageableEntity {
  private:
    uint16_t id;
    AnimationHandler anim;
    GameMap& map;
    int points;
    float revive_cooldown;
    int poisoned;
    float poisoned_cooldown;
    std::vector<Gun> guns;
    int currentGun;
    std::string player_name;
  public:
    PlayerEntity(float x, float y, int id, int health, std::string name, GameMap& map, int characterID);
    const char* name() override;
    std::optional<Player> asPlayer() override;
    bool send(const std::string& cmd) override;
    void tick(GameMap& map, float deltaT) override;
    void onDie() override;
    bool isPlayer() override;
    void damage(int dp) override;
    Passability onCollision(Entity& other, Axis axis) override;
    ~PlayerEntity() {};
};

#endif
