#ifndef PLAYERMAP_H
#define PLAYERMAP_H

#include "gamemap.h"
#include "level.h"

#include <unordered_map>

class PlayerMap
{
private:
  GameMap &map;
  std::unordered_map<int, int> players;

public:
  PlayerMap(GameMap &map);
  void handleJoin(Level &level, int clientID, std::string player_name, int characterID);
  void handleLeave(int clientID);
  void moveLeft(int clientID, bool is_fast);
  void moveRight(int clientID, bool is_fast);
  void jump(int clientID);
  void shoot(int clientID);
  bool enoughPlayers();
  bool notJoined(int clientID);
  void clear();
  int playerCount();
  void switchGun(int clientID);
  void stopMoving(int clientID);
  void combo(int clientID);
  void StopShooting(int clientID);
  void ammoFull(int clientID);
};

#endif
