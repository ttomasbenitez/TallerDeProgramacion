#include "level.h"
#include "gamelogic/entities/testent.h"
#include "gamelogic/entities/bullet.h"
#include "gamelogic/entities/edges.h"
#include "gamelogic/entities/wandering.h"
#include "gamelogic/entities/static.h"
#include "gamelogic/entities/spikes.h"
#include "gamelogic/entities/platform.h"
#include "gamelogic/entities/landscape.h"
#include "gamelogic/entities/floatingplatform.h"
#include "gamelogic/entities/stairs.h"
#include "gamelogic/entities/coin.h"
#include "gamelogic/entities/bridge.h"
#include "gamelogic/entities/tall_platform.h"
#include "gamelogic/entities/posionfruit.h"

Level::Level(const char *filename) : level(YAML::LoadFile(filename)) {}

void Level::loadEntities(GameMap &map)
{
  float minY = 0, maxY = 0;
  float minX = 0, maxX = 0;
  map.clear();
  for (size_t i = 0; i < level["entities"].size(); i++)
  {
    //fillEntity(map, level["entities"][i]);
    map.add(this->loadEntity(level["entities"][i]));
    float entX = level["entities"][i]["x"].as<float>();
    float entY = level["entities"][i]["y"].as<float>();
    if (entX < minX)
      minX = entX;
    if (entX > maxX)
      maxX = entX;
    if (entY < minY)
      minY = entY;
    if (entY > maxY)
      maxY = entY;
  }
  map.add(std::make_unique<EdgesEntity>(level["width"].as<float>(), level["height"].as<float>(), minX, minY));
}

void Level::fillEntity(GameMap &map, YAML::Node e)
{
  float width = level["width"].as<float>();
  auto type = e["type"].as<std::string>();
  if (type == "Floor")
  {
    auto entity = std::make_unique<Platform>(e["x"].as<float>(), e["y"].as<float>(), e["id"].as<int>());
    for (size_t i = 0; i * entity->getX() + entity->getWidth() * i < width; i++)
    {
      map.add(std::make_unique<Platform>((e["x"].as<float>()) + entity->getWidth() * i, e["y"].as<float>(), e["id"].as<int>()));
    }
  }
  if (type == "Landscape")
  {
    auto entity = std::make_unique<Landscape>(e["x"].as<float>(), e["y"].as<float>(), e["id"].as<int>());

    for (size_t i = 0; i * entity->getX() + entity->getWidth() * i < entity->getX() + width; i++)
    {
      map.add(std::make_unique<Landscape>((e["x"].as<float>()) + entity->getWidth() * i, e["y"].as<float>(), e["id"].as<int>()));
    }
  }
}

std::unique_ptr<Entity> Level::loadEntity(YAML::Node e)
{
  auto type = e["type"].as<std::string>();
  if (type == "Spikes")
    return std::make_unique<SpikesEntity>(e["x"].as<float>(), e["y"].as<float>());
  if (type == "ExitSign" || type == "RedMushroom" || type == "Arrow" || type == "Algae")
    return std::make_unique<Static>(e["x"].as<float>(), e["y"].as<float>(), e["id"].as<int>());
  if (type == "Wandering")
    return std::make_unique<WanderingEntity>(e["x"].as<float>(), e["y"].as<float>(), e["id"].as<int>());
  if (type == "Fish")
    return std::make_unique<WanderingEntity>(e["x"].as<float>(), e["y"].as<float>(), e["id"].as<int>());
  if (type == "Crab")
    return std::make_unique<WanderingEntity>(e["x"].as<float>(), e["y"].as<float>(), e["id"].as<int>());
  if (type == "Turtle")
    return std::make_unique<WanderingEntity>(e["x"].as<float>(), e["y"].as<float>(), e["id"].as<int>());
  if (type == "madHatter" || type == "skeleton")
    return std::make_unique<WanderingEntity>(e["x"].as<float>(), e["y"].as<float>(), e["id"].as<int>());
  if (type == "Floor")
    return std::make_unique<Platform>(e["x"].as<float>(), e["y"].as<float>(), e["id"].as<int>());
  if (type == "FloatingFloor")
    return std::make_unique<Bridge>(e["x"].as<float>(), e["y"].as<float>(), e["id"].as<int>());
  if (type == "Rise")
    return std::make_unique<Stair>(e["x"].as<float>(), e["y"].as<float>(), e["id"].as<int>(), 1, true);
  if (type == "Descent")
    return std::make_unique<Stair>(e["x"].as<float>(), e["y"].as<float>(), e["id"].as<int>(), -1, true);
  if (type == "RisePsychedelia")
    return std::make_unique<Stair>(e["x"].as<float>(), e["y"].as<float>(), e["id"].as<int>(), 1, false);
  if (type == "DescentPsychedelia")
    return std::make_unique<Stair>(e["x"].as<float>(), e["y"].as<float>(), e["id"].as<int>(), -1, false);
  if (type == "Platform")
    return std::make_unique<Platform>(e["x"].as<float>(), e["y"].as<float>(), e["id"].as<int>());
  if (type == "FloorPsychedelia")
    return std::make_unique<TallPlatform>(e["x"].as<float>(), e["y"].as<float>(), e["id"].as<int>(), false);
  if (type == "stoneTowerFloor")
    return std::make_unique<TallPlatform>(e["x"].as<float>(), e["y"].as<float>(), e["id"].as<int>(), true);
  if (type == "FloatingPlatform" || type == "StoneTower")
    return std::make_unique<Platform>(e["x"].as<float>(), e["y"].as<float>(), e["id"].as<int>());
  if (type == "Gem" || type == "Coin")
    return std::make_unique<CoinEntity>(e["x"].as<float>(), e["y"].as<float>(), e["id"].as<int>());
  if (type == "Landscape")
    return std::make_unique<Landscape>(e["x"].as<float>(), e["y"].as<float>(), e["id"].as<int>());
  if (type == "PoisonFruit")
    return std::make_unique<PoisonedFruitEntity>(e["x"].as<float>(), e["y"].as<float>(), e["id"].as<int>());
  if (type == "Rocks" || type == "ExitSignPsychedelia" || type == "ColumnStonesLower" || type == "ColumnStones" || type == "ColumnStonesLowerRight" || type == "ColumnStonesRight")
    return std::make_unique<Platform>(e["x"].as<float>(), e["y"].as<float>(), e["id"].as<int>());

  throw std::runtime_error("Invalid entity type found while loading level." + type);
}

int Level::getBackground()
{
  return level["background"].as<int>();
}

std::pair<float, float> Level::getSpawnPoint(GameMap &map)
{
  for (size_t i = 0; i < level["player_spawn_points"].size(); i++)
  {
    const auto &point = level["player_spawn_points"][i];
    float x = point["x"].as<float>(), y = point["y"].as<float>();
    /*if (map.isFree(x, y, 1, 2))*/ return {x, y};
  }
  throw std::runtime_error("No valid spawn points found.");
}
