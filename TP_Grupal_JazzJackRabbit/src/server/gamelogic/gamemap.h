#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <unordered_map>
#include <map>
#include <memory>
#include <functional>

#include "entity.h"
#include "gamestate.h"

class Level;

class GameMap {
  private:
    int id_counter;
    std::map<int, std::unique_ptr<Entity>> entities;
  public:
    GameMap();
    int add(std::unique_ptr<Entity> entity);
    void remove(int id);
    bool isAlive(int id);
    void clear();
    void map(const std::function<void(int, Entity&)>& func);
    void applyTo(int id, const std::function<void(Entity&)>& func);
    bool isFree(float x, float y, float width, float height);
    void reap(Level& level);
    GameState dumpState(Level& level, uint16_t sec_left);
};

#endif
