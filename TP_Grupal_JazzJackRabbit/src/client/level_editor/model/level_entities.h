#ifndef LEVEL_ENTITES_H
#define LEVEL_ENTITES_H

#include <vector>
#include <map>
#include <string>
#include <cstdint>
#include "../../../common/sprites_frames.h"
#include "../../../common/enums.h"
#include "../../../common/entities_sizes.h"

enum Passability : uint8_t
{
    PASSABLE,
    IMPASSABLE,
};

struct AnimationInfo
{
    std::string animationPath;
    Frame displayFrame;
};

struct LevelEntity
{
    std::string type;
    AnimationState id;
    Passability passability;
    int x;
    int y;
    Size sz;
    AnimationInfo animation;
    // Habría que agregar música también.
};

struct LevelData
{
    int scenery;
    int background;
    std::map<int, LevelEntity> entities;
};

#endif // LEVEL_ENTITES_H
