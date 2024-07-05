#ifndef LEVEL_PARSER_H
#define LEVEL_PARSER_H

#include <iostream>
#include <cstdint>
#include <string>
#include "level_entities.h"
#include <yaml-cpp/yaml.h>
#include "../../../common/enums.h"
#include "../../sprites_path.h"
#include <fstream>
#include "../../../common/entities_sizes.h"
#include "../../../common/entities_names.h"

class LevelParser
{
private:
    YAML::Node level;

public:
    LevelParser();
    LevelParser(const char *filename);

    void loadAnimationInfo(LevelEntity &entity);
    void loadEntityInfo(LevelEntity &entity);
    LevelData readLevelData();
    int getScenery();
    void writeLevelData(const std::string &filePath, const LevelData &levelData);
    ~LevelParser() = default;
};

#endif // LEVEL_PARSER_H
