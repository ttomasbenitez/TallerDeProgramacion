#include "gamemanager.h"
#include "config.h"

#include <sstream>
#include <string>

void GameManager::route(ClientMessage &msg)
{
  this->reap();
  std::unique_lock<std::mutex> lck(maps_mtx);
  int clientID = msg.first;
  Action type = msg.second.action;
  if (clients.count(clientID))
  {
    if (type == Action::Join)
      return;
    if (type == Action::Create)
      return;
    games[clients[clientID]]->get_c2s_queue().push(msg);
  }
  else
  {
    handleUnjoinedCmd(msg, lck);
  }
}

void GameManager::handleUnjoinedCmd(ClientMessage &msg, std::unique_lock<std::mutex> &lck)
{
  int clientID = msg.first;
  Action type = msg.second.action;
  switch (type)
  {
  case Action::Create:
  {
    int gameID = this->game_counter++;
    games[gameID] = std::make_unique<Gameloop>(gameID, *this, msg.second.path);
    games[gameID]->start();
    clients[clientID] = gameID;
    ClientAction ca(Action::Join, gameID, msg.second.data, msg.second.name);
    ClientMessage cm(clientID, ca);
    games[gameID]->get_c2s_queue().push(cm);
    break;
  }
  case Action::Join:
  {
    int gameID = msg.second.data;
    if (!games.count(gameID))
      return;
    if (games[gameID]->getState() != MatchState::Joining)
      return;
    clients[clientID] = gameID;
    games[gameID]->get_c2s_queue().push(msg);
    break;
  }
  case Action::List:
  {
    std::vector<AvailableGame> ag;
    for (auto &[gameID, game] : games)
    {
      if (game->getState() != MatchState::Joining)
        continue;
      ag.push_back(AvailableGame{
          (uint16_t)gameID,
          (uint8_t)game->playerCount(),
          config.get<uint8_t>("game.players")});
    }
    auto reply = GameState::makeGameList(clientID, ag);
    s2c_queues[clientID]->push(reply);
    break;
  }
  default:
    break;
  }
}

Queue<ClientMessage> &GameManager::get_c2s_queue()
{
  return c2s_queue;
}

void GameManager::broadcast(int gameID, GameState msg)
{
  std::unique_lock lck(maps_mtx);
  for (auto &[clientID, clientGameID] : clients)
  {
    if (clientGameID == gameID)
    {
      try
      {
        s2c_queues[clientID]->push(msg);
      }
      catch (const ClosedQueue &e)
      {
        continue;
      }
    }
  }
}

int GameManager::add_client(std::shared_ptr<Queue<GameState>> queue)
{
  std::unique_lock lck(maps_mtx);
  int clientID = this->client_counter++;
  s2c_queues[clientID] = queue;
  return clientID;
}

void GameManager::remove_client(int clientID)
{
  std::unique_lock lck(maps_mtx);
  s2c_queues.erase(clientID);
  clients.erase(clientID);
}

void GameManager::quit_client(int clientID)
{
  std::unique_lock lck(maps_mtx);
  if (clients.count(clientID))
  {
    int gameID = clients[clientID];
    if (games[gameID]->playerCount() == 0)
    {
      to_reap.push_back(gameID);
    }
  }
  clients.erase(clientID);
}

void GameManager::closeGame(int gameID)
{
  std::unique_lock lck(maps_mtx);
  to_reap.push_back(gameID);
}

void GameManager::stop()
{
  std::unique_lock lck(maps_mtx);
  for (auto &[_, game] : games)
  {
    if (game->is_alive())
      game->stop();
  }
  for (auto &[_, queue] : s2c_queues)
  {
    queue->close();
  }
}

void GameManager::join()
{
  maps_mtx.lock();
  for (auto &[_, game] : games)
  {
    maps_mtx.unlock();
    game->join();
    maps_mtx.lock();
  }
}

void GameManager::reap()
{
  std::unique_lock lck(maps_mtx);
  for (auto it = to_reap.begin(); it != to_reap.end();)
  {
    int gameID = *it;
    if (!games.count(gameID))
    {
      it = to_reap.erase(it);
      continue;
    }
    auto &game = games[gameID];
    if (!game->is_alive())
    {
      game->join();
      games.erase(gameID);
      it = to_reap.erase(it);
      continue;
    }
    this->_exitClients(gameID, lck);
    game->stop();
    it++;
  }
}

void GameManager::exitClients(int gameID)
{
  std::unique_lock lck(maps_mtx);
  this->_exitClients(gameID, lck);
}

void GameManager::_exitClients(int gameID, std::unique_lock<std::mutex> &lck)
{
  for (auto it = clients.begin(); it != clients.end();)
  {
    auto &[clientID, clientGameID] = *it;
    if (clientGameID == gameID)
    {
      s2c_queues[clientID]->close();
      s2c_queues.erase(clientID);
      it = clients.erase(it);
    }
    else
    {
      it++;
    }
  }
}

void GameManager::pushCommand(std::string cmd)
{
  std::unique_lock lck(maps_mtx);
  if (cmd == "listGames")
  {
    std::cout << "Games: ";
    for (auto &[gameID, game] : games)
    {
      std::cout << gameID;
    }
    std::cout << std::endl;
    return;
  }
  std::stringstream ss(cmd);
  int gameID;
  std::string rest;
  ss >> gameID;
  std::getline(ss, rest);
  if (games.count(gameID))
    games[gameID]->pushCommand(rest);
}
