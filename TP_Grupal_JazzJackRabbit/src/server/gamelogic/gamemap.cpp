#include "gamemap.h"
#include "level.h"

GameMap::GameMap() : id_counter(0) {}

int GameMap::add(std::unique_ptr<Entity> entity)
{
  entities[id_counter] = std::move(entity);
  return id_counter++;
}

void GameMap::remove(int id)
{
  entities.erase(id);
}

void GameMap::clear()
{
  entities.clear();
}

void GameMap::map(const std::function<void(int, Entity &)> &func)
{
  for (auto const &[id, entity] : entities)
  {
    func(id, *entity);
  }
}

void GameMap::applyTo(int id, const std::function<void(Entity &)> &func)
{
  if (!entities.count(id))
    throw std::runtime_error("Non-existing entity ID.");
  func(*entities[id]);
}

void GameMap::reap(Level &level)
{
  for (auto it = entities.begin(); it != entities.end();)
  {
    auto &entity = it->second;
    if (entity->isDead())
    {
      if (entity->asPlayer())
      {
        auto [x, y] = level.getSpawnPoint(*this);
        entity->setX(x);
        entity->setY(y);
        entity->send("revive");
      }
      else
      {
        it = entities.erase(it);
      }
    }
    else
    {
      it++;
    }
  }
}

GameState GameMap::dumpState(Level &level, uint16_t sec_left)
{
  std::vector<RenderableGameEntity> re;
  std::vector<Player> pl;
  for (auto &[id, entity] : entities)
  {
    auto maybe_player = entity->asPlayer();
    if (maybe_player)
    {
      pl.push_back(maybe_player.value());
    }
    else
    {
      re.push_back(entity->render());
    }
  }
  auto gs = GameState::makeGameState(level.getBackground(), sec_left, pl, re);
  return gs;
}

bool GameMap::isFree(float x, float y, float width, float height)
{
  Entity testEnt(x, y, width, height);
  bool valid = true;
  this->map([&](int id, Entity &entity)
            { valid &= !entity.isColliding(testEnt); });
  return valid;
}

bool GameMap::isAlive(int id)
{
  if (!entities.count(id))
    return false;
  return !entities[id]->isDead();
}
