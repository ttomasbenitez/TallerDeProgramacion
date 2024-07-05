#include "level_parser.h"

LevelParser::LevelParser() {}
LevelParser::LevelParser(const char *filename) : level(YAML::LoadFile(filename)) {}

void LevelParser::loadAnimationInfo(LevelEntity &entity)
{
    entity.animation.displayFrame = animations_frames.at(entity.id)[0];
    entity.animation.animationPath = sprites_path.at(entity.id);
    entity.sz = entities_sizes.at(entity.id);
}

void LevelParser::loadEntityInfo(LevelEntity &entity)
{
    loadAnimationInfo(entity);
    switch (entity.id)
    {
    case GEM:
    case BEACH_LANDSCAPE:
    case BEACH_EXIT_SIGN:
    case SPAWN_POINT:
    case BEACH_ALGAE:
    case COIN:
        entity.passability = PASSABLE;
        break;
    default:
        entity.passability = IMPASSABLE;
        break;
    }
}

int LevelParser::getScenery()
{
    return level["scenery"].as<int>();
}

LevelData LevelParser::readLevelData()
{
    LevelData levelData;
    //    YAML::Node level = YAML::LoadFile(filePath);

    levelData.background = level["background"].as<int>();
    levelData.scenery = getScenery();

    for (const auto &node : level["entities"])
    {
        LevelEntity entity;
        entity.id = (AnimationState)node["id"].as<uint8_t>();
        entity.type = node["type"].as<std::string>();
        entity.x = node["x"] ? node["x"].as<int>() : 0;
        entity.y = node["y"] ? node["y"].as<int>() : 0;

        loadEntityInfo(entity);

        levelData.entities[levelData.entities.size()] = entity;
    }

    for (const auto &node : level["player_spawn_points"])
    {
        LevelEntity entity;

        entity.type = "SpawnPoint";
        entity.id = SPAWN_POINT;
        entity.x = node["x"] ? node["x"].as<int>() : 0;
        entity.y = node["y"] ? node["y"].as<int>() : 0;

        loadEntityInfo(entity);

        levelData.entities[levelData.entities.size()] = entity;
    }

    return levelData;
}

void LevelParser::writeLevelData(const std::string &filePath, const LevelData &levelData)
{
    YAML::Node level;

    level["scenery"] = levelData.scenery;
    level["background"] = levelData.background;
    int width = 0;
    int height = 480;

    std::vector<LevelEntity> spawnPoints;

    YAML::Node entitiesNode;
    for (auto it = levelData.entities.begin(); it != levelData.entities.end(); ++it)
    {
        if (it->second.id == SPAWN_POINT)
        {
            spawnPoints.push_back(it->second);
            continue;
        }

        YAML::Node entityNode;
        LevelEntity entity = it->second;

        entityNode["type"] = entity.type;
        entityNode["id"] = (int)entity.id;
        entityNode["x"] = entity.x;
        entityNode["y"] = entity.y;
        if (entity.x > width)
        {
            width = entity.x + entity.sz.width;
        }
        if (entity.y < 0 && abs(entity.y) + 480 > height)
        {
            height = abs(entity.y) + 480;
        }
        entitiesNode.push_back(entityNode);
    }
    level["width"] = width;
    level["height"] = height;
    level["entities"] = entitiesNode;

    YAML::Node spawnPointsNode;

    for (LevelEntity &sp : spawnPoints)
    {
        YAML::Node spawnPointNode;

        spawnPointNode["x"] = sp.x;
        spawnPointNode["y"] = sp.y;

        spawnPointsNode.push_back(spawnPointNode);
    }
    level["player_spawn_points"] = spawnPointsNode;

    std::ofstream outputFile(filePath);
    outputFile << level;
}
