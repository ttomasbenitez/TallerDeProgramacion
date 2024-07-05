#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "queue.h"
#include "thread.h"
#include "clientaction.h"
#include "gamestate.h"
#include "config.h"
#include "entity.h"
#include "level.h"
#include "gamemap.h"
#include "playermap.h"
#include "gamemanager.h"

#include <memory>
#include <functional>
#include <atomic>

class GameManager;

enum class MatchState : uint8_t
{
  Joining,
  Playing,
  Ended
};

class Gameloop : public Thread
{
private:
  int gameID;
  GameManager &games;
  Queue<ClientMessage> c2s_queue;
  Queue<std::string> cmd_queue;
  GameMap map;
  Level level;
  int last_iter;
  int iter_started;
  bool paused;
  bool debug;
  std::atomic<MatchState> state;
  PlayerMap players;

  void loadLevel(const char *filename);
  void tick(int it);
  void processAction(ClientMessage &action);
  void processCommand(std::string cmd);
  float toInGameTime(int iters);
  void processActionsCommands();

public:
  explicit Gameloop(int gameID, GameManager &games, std::string path);
  Queue<ClientMessage> &get_c2s_queue();
  void run() override;
  void pushCommand(std::string cmd);
  MatchState getState();
  void stop() override;
  int playerCount();
  ~Gameloop() {}
};

#endif
