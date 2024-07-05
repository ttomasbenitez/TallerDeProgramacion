#ifndef ENTITIES_NAMES_H
#define ENTITIES_NAMES_H

#include <iostream>
#include <vector>
#include "enums.h"
#include <map>

const std::map<enum AnimationState, std::string> entities_names = {
        {SPAWN_POINT, "SpawnPoint"},
        {CRAB, "Crab"},
        {FISH, "Fish"},
        {TURTLE, "Turtle"},
        {GEM, "Gem"},
        {BEACH_LANDSCAPE, "BeachLandscape"},
        {BEACH_FLOOR, "BeachFloor"},
        {BEACH_FLOATING_FLOOR, "BeachFloatingFloor"},
        {BEACH_PLATFORM, "BeachPlatform"},
        {BEACH_FLOATING_PLATFORM, "BeachFloatingFloor"},
        {BEACH_RISE_DESCENT, "BeachRiseDescent"},
        {BEACH_DESCENT, "BeachDescent"},
        {BEACH_RISE, "BeachRise"},
        {BEACH_EXIT_SIGN, "BeachExitSign"},
};

#endif //ENTITIES_NAMES_H
