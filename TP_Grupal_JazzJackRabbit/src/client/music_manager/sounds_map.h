#ifndef SOUNDS_MAP_H
#define SOUNDS_MAP_H

#include <iostream>
#include <memory>
#include "../../common/enums.h"
#include <map>
#include <SDL2pp/SDL2pp.hh>
using namespace SDL2pp;
#include <SDL2pp/Mixer.hh>

std::unordered_map<AnimationState, std::unique_ptr<Chunk>> initSoundMap();

#endif //SOUNDS_MAP_H
