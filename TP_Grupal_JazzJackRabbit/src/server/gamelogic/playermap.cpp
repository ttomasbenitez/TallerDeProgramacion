#include "config.h"
#include "playermap.h"
#include "entity.h"
#include "entities/player.h"

#include <memory>
#include <cstring>

PlayerMap::PlayerMap(GameMap &map) : map(map), players() {}

void PlayerMap::handleJoin(Level &level, int clientID, std::string player_name, int characterID)
{
  if (this->enoughPlayers())
    throw std::runtime_error("Enough players already.");
  auto [x, y] = level.getSpawnPoint(map);
  auto player = std::make_unique<PlayerEntity>(x, y, clientID, config.get<int>("game.player_health"), player_name, map, characterID);
  int entityID = map.add(std::move(player));
  players[clientID] = entityID;
}

void PlayerMap::handleLeave(int clientID)
{
  if (this->notJoined(clientID))
    throw std::runtime_error("No such player.");
  map.remove(players[clientID]);
  players.erase(clientID);
}

bool PlayerMap::enoughPlayers()
{
  return this->playerCount() == config.get<int>("game.players");
}

int PlayerMap::playerCount()
{
  int count = 0;
  map.map([&](int id, Entity &entity)
          {
    if(std::strcmp(entity.name(), "PlayerEntity") == 0) count++; });
  return count;
}

void PlayerMap::moveLeft(int clientID, bool is_fast)
{
  if (this->notJoined(clientID))
    throw std::runtime_error("No such player.");
  map.applyTo(players[clientID], [&](Entity &player)
              {
    if (is_fast) {
      player.send("left_fast");
    } else {
      player.send("left");
    } });
}

void PlayerMap::moveRight(int clientID, bool is_fast)
{
  if (this->notJoined(clientID))
    throw std::runtime_error("No such player.");
  map.applyTo(players[clientID], [&](Entity &player)
              {
    if (is_fast) {
      player.send("right_fast");
    } else {
      player.send("right");
    } });
}

void PlayerMap::jump(int clientID)
{
  if (this->notJoined(clientID))
    throw std::runtime_error("No such player.");
  map.applyTo(players[clientID], [&](Entity &player)
              { player.send("jump"); });
}

void PlayerMap::combo(int clientID)
{
  if (this->notJoined(clientID))
    throw std::runtime_error("No such player.");
  map.applyTo(players[clientID], [&](Entity &player)
              { player.send("combo"); });
}

void PlayerMap::shoot(int clientID)
{
  if (this->notJoined(clientID))
    throw std::runtime_error("No such player.");
  map.applyTo(players[clientID], [&](Entity &player)
              { player.send("shoot"); });
}

void PlayerMap::switchGun(int clientID)
{
  if (this->notJoined(clientID))
    throw std::runtime_error("No such player.");
  map.applyTo(players[clientID], [&](Entity &player)
              { player.send("switch_gun"); });
}

void PlayerMap::stopMoving(int clientID)
{
  if (this->notJoined(clientID))
    throw std::runtime_error("No such player.");
  map.applyTo(players[clientID], [&](Entity &player)
              { player.send("stop_moving"); });
}

void PlayerMap::StopShooting(int clientID)
{
  if (this->notJoined(clientID))
    throw std::runtime_error("No such player.");
  map.applyTo(players[clientID], [&](Entity &player)
              { player.send("stop_shooting"); });
}


void PlayerMap::ammoFull(int clientID){
  std::string msg("full_ammo");
  if (this->notJoined(clientID)) throw std::runtime_error("No such player.");
  map.applyTo(players[clientID], [&](Entity& player) {
    player.send("full_ammo");
  });
}

void PlayerMap::clear()
{
  players.clear();
}

bool PlayerMap::notJoined(int clientID)
{
  return !players.count(clientID);
}
