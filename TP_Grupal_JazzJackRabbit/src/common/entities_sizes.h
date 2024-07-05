#ifndef ENTITIES_SIZES_H
#define ENTITIES_SIZES_H

#include <iostream>
#include <vector>
#include "enums.h"
#include <map>

struct Size
{
    int width;
    int height;
};

const std::map<enum AnimationState, Size> entities_sizes = {
    {JAZZ, {78, 40}},
    {LORI, {78, 40}},
    {SPAZ, {78, 40}},
    {BULLET, {20, 10}},
    {SHOT_RED_ROCKET, {40, 20}},
    {SHOT_FIREBALL, {20, 10}},
    {SPAWN_POINT, {100, 100}},
    {CRAB, {70, 70}},
    {FISH, {80, 80}},
    {TURTLE, {100, 100}},
    {RED_ROCKET, {30, 30}},
    {FIREBALL, {50, 50}},
    {GEM, {50, 50}},
    {COIN, {50, 50}},
    {POISON_FRUIT, {30, 30}},
    {BEACH_LANDSCAPE, {700, 200}},
    {BEACH_FLOOR, {300, 50}},
    {BEACH_FLOATING_FLOOR, {300, 55}},
    {BEACH_PLATFORM, {300, 350}},
    {BEACH_FLOATING_PLATFORM, {200, 40}},
    {BEACH_RISE_DESCENT, {1000, 300}},
    {BEACH_DESCENT, {200, 200}},
    {BEACH_RISE, {200, 200}},
    {BEACH_EXIT_SIGN, {50, 50}},
    {BEACH_ALGAE, {50, 50}},
    // AIW
    {ARROW, {50, 50}},
    {FLOOR_AIW, {308, 100}},
    {GUITAR, {700, 200}},
    {CHESIRE, {90, 90}},
    {DESCENT, {211, 261}},
    {RISE, {211, 261}},
    {RED_MUSHROOM, {50, 50}},
    {EXIT, {50, 50}},
    {ROCKS, {307, 164}},
    {ROCKS3_AIW, {307, 164}},
    {FLOOR2_AIW, {372, 100}},
    {FLOOR3_AIW, {372, 100}},
    {FLOOR4_AIW, {386, 100}},
    {ROCKS2_AIW, {62, 164}},
    {STONE_TOWER, {227, 258}},
    {COLUMN_STONES, {392, 281}},
    {COLUMN_STONES_RIGHT, {392, 281}},
    {COLUMN_STONES_LOWER, {374, 224}},
    {COLUMN_STONES_LOWER_RIGHT, {374, 224}},
    {FLOOR_AFTER_RAISE, {136, 100}},
    {ROCKS_AFTER_RAISE, {134, 163}},
    {FLOOR_BEFORE_DESCENT, {136, 100}},
    {ROCKS_BEFORE_DESCENT, {134, 163}},
    {FLOOR_STONE_TOWER, {220, 63}},
    {MAD_HATTER, {60, 65}},
    {SKELETON, {60, 65}},
};

#endif // ENTITIES_SIZES_H
