#ifndef LEVEL_H
#define LEVEL_H

#include "entity.h"
#include "gamemap.h"

#include <yaml-cpp/yaml.h>
#include <list>
#include <memory>

class Level
{
private:
  YAML::Node level;
  std::unique_ptr<Entity> loadEntity(YAML::Node e);
  void fillEntity(GameMap &map, YAML::Node e);

public:
  explicit Level(const char *filename);
  void loadEntities(GameMap &map);
  int getBackground();
  std::pair<float, float> getSpawnPoint(GameMap &);
};

#endif
