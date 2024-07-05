#include "sounds_map.h"

std::unordered_map<AnimationState, std::unique_ptr<Chunk>> initSoundMap() {
    std::unordered_map<AnimationState, std::unique_ptr<Chunk>> soundMap;


    auto bulletSound = std::make_unique<Chunk>(DATA_PATH "/audio/shot.wav");
    auto jumpSound = std::make_unique<Chunk>(DATA_PATH "/audio/jump.wav");
    auto landingSound = std::make_unique<Chunk>(DATA_PATH "/audio/land.wav");
    auto coinPickupSound = std::make_unique<Chunk>(DATA_PATH "/audio/coin.wav");
    auto hurtSound = std::make_unique<Chunk>(DATA_PATH "/audio/hurt.wav");
    auto dyingSound = std::make_unique<Chunk>(DATA_PATH "/audio/die.wav");
    auto explosion = std::make_unique<Chunk>(DATA_PATH "/audio/explosion.wav");
    auto fireball = std::make_unique<Chunk>(DATA_PATH "/audio/burn.wav");
    auto dyingEnemy = std::make_unique<Chunk>(DATA_PATH "/audio/deadEnemy.wav");
    auto poisoned = std::make_unique<Chunk>(DATA_PATH "/audio/poison.wav");

    soundMap[BULLET_SOUND] = (std::move(bulletSound));
    soundMap[RED_ROCKET_SOUND] = (std::move(explosion));
    soundMap[FIREBALL_SOUND] = (std::move(fireball));
    soundMap[COIN_SOUND] = (std::move(coinPickupSound));
    soundMap[HURT_SOUND] = (std::move(hurtSound));
    soundMap[DYING_SOUND] = (std::move(dyingSound));
    soundMap[LANDING_SOUND] = (std::move(landingSound));
    soundMap[DYING_ENEMY_SOUND] = (std::move(dyingEnemy));
    soundMap[POISONED_SOUND] = (std::move(poisoned));


    return soundMap;
}
