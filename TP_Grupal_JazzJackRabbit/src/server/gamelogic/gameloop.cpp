#include "gameloop.h"
#include "config.h"
#include "constant_rate.h"

#include <string>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <functional>

Gameloop::Gameloop(int gameID, GameManager &games, std::string path) : gameID(gameID),
                                                                       games(games),
                                                                       c2s_queue(config.get<int>("limits.recvq")),
                                                                       level(path.c_str()),
                                                                       last_iter(0),
                                                                       iter_started(0),
                                                                       paused(config.get<bool>("start_paused")),
                                                                       debug(false),
                                                                       state(MatchState::Joining),
                                                                       players(this->map)
{
  this->level.loadEntities(this->map);
}

void Gameloop::run()
{
  ConstantRateLooper loop(config.get<double>("physics.tps"), [game = this](int it)
                          {
    game->processActionsCommands();
    if (game->state == MatchState::Playing) game->tick(it);
    game->last_iter = it;
    return game->_keep_running.load(); });
  loop.run();
  this->_is_alive = false;
}

Queue<ClientMessage> &Gameloop::get_c2s_queue()
{
  return this->c2s_queue;
}

float Gameloop::toInGameTime(int iters)
{
  return config.get<double>("physics.scaler") * float(iters) / config.get<double>("physics.tps");
}

void Gameloop::processActionsCommands()
{
  for (std::string cmd; this->cmd_queue.try_pop(cmd);)
  {
    this->processCommand(cmd);
  }
  for (ClientMessage action; this->c2s_queue.try_pop(action);)
  {
    this->processAction(action);
  }
}

void Gameloop::tick(int iter_num)
{
  int deltaIter = iter_num - last_iter;
  if (deltaIter > 1)
    std::cout << "lost " << deltaIter - 1 << " ticks" << std::endl;
  float deltaT = this->toInGameTime(deltaIter);
  if (!paused)
    this->map.map([&](int id, Entity &entity)
                  { entity.applyDeltaV(0, -config.get<float>("physics.gravity") * deltaT); });
  if (!paused)
    this->map.map([&](int id, Entity &entity)
                  { entity.tick(this->map, deltaT); });
  this->map.reap(level);
  if (debug)
    this->map.map([&](int id, Entity &entity) { // debug (REMOVE LATER)
      printf("%s #%i (%f,%f)\n", entity.name(), id, entity.getX(), entity.getY());
    });
  int time_left = config.get<float>("game.length_secs") - this->toInGameTime(iter_num - iter_started);
  if (time_left < 0)
  {
    std::cout << "Game ended." << std::endl;
    this->state = MatchState::Ended;
    this->games.closeGame(gameID);
    this->games.exitClients(gameID);
    return;
  }
  this->games.broadcast(gameID, this->map.dumpState(this->level, time_left));
}

void Gameloop::processAction(ClientMessage &msg)
{
  int id = msg.first;
  Action action = msg.second.action;
  int param1 = msg.second.data;
  int param2 = msg.second.data2;
  if (players.notJoined(id) && action != Action::Join)
    return;
  switch (action)
  {
  case Action::Join:
  {
    players.handleJoin(level, id, msg.second.name, msg.second.data2);
    if (players.enoughPlayers())
    {
      this->state = MatchState::Playing;
      iter_started = last_iter;
    }
    break;
  }
  case Action::Quit:
  {
    players.handleLeave(id);
    games.quit_client(id);
    break;
  };
  case Action::Left:
    return players.moveLeft(id, param1);
  case Action::Right:
    return players.moveRight(id, param1);
  case Action::Jump:
    return players.jump(id);
  case Action::Shoot:
    return players.shoot(id);
  case Action::SwitchGun:
    return players.switchGun(id);
  case Action::StopMoving:
    return players.stopMoving(id);
  case Action::Ammo:
    return players.ammoFull(id);
  case Action::Combo:
    return players.combo(id);
  case Action::StopShooting:
    return players.StopShooting(id);
  default:
    break;
  }
}

void Gameloop::processCommand(std::string line)
{
  std::istringstream lineiss(line);
  std::string cmd;
  lineiss >> cmd;
  if (cmd == "list")
  {
    this->map.map([&](int id, Entity &entity)
                  { printf("%s #%i (%f,%f)\n", entity.name(), id, entity.getX(), entity.getY()); });
  }
  if (cmd == "players")
  {
    this->map.map([&](int id, Entity &entity)
                  {
      auto maybePlayer = entity.asPlayer();
      if (maybePlayer) {
        Player player = maybePlayer.value();
        printf("%s #%i (%f,%f) h=%i p=%i\n", player.name.data(), id,entity.getX(), entity.getY(), player.health, player.points);
      } });
  }
  if (cmd == "damage")
  {
    int id, damage;
    lineiss >> id >> damage;
    this->map.applyTo(id, [&](Entity &e)
                      { e.damage(damage); });
  }
  if (cmd == "tp")
  {
    int id, x, y;
    lineiss >> id >> x >> y;
    this->map.applyTo(id, [&](Entity &e)
                      { e.tryMove(x, y, this->map); });
  }
  if (cmd == "pause")
    paused = true;
  if (cmd == "unpause")
    paused = false;
  if (cmd == "enableDebug")
    debug = true;
  if (cmd == "disableDebug")
    debug = false;
  if (cmd == "tick")
  {
    this->map.map([&](int id, Entity &entity)
                  { entity.tick(this->map, 0.1); });
  }
  if (cmd == "level")
  {
    std::string filename;
    lineiss >> filename;
    this->level = Level(filename.c_str());
    this->level.loadEntities(this->map);
  }
}

void Gameloop::pushCommand(std::string cmd)
{
  this->cmd_queue.push(cmd);
}

MatchState Gameloop::getState()
{
  return state;
}

void Gameloop::stop()
{
  Thread::stop();
  this->state = MatchState::Ended;
}

int Gameloop::playerCount()
{
  return this->players.playerCount();
}
