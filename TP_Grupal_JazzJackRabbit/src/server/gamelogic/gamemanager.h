#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "queue.h"
#include "clientaction.h"
#include "gameloop.h"

#include <unordered_map>
#include <mutex>
#include <memory>

class Gameloop;

class GameManager {
  private:
    int game_counter;
    int client_counter;
    Queue<ClientMessage> c2s_queue;
    std::mutex maps_mtx;
    std::unordered_map<int, std::unique_ptr<Gameloop>> games; // gameID -> game
    std::unordered_map<int, std::shared_ptr<Queue<GameState>>> s2c_queues; // clientID -> queue 
    std::unordered_map<int, int> clients; // clientID -> gameID
    std::list<int> to_reap; // games pending deletion
    void handleUnjoinedCmd(ClientMessage& msg, std::unique_lock<std::mutex>& lck);
    void _exitClients(int gameID, std::unique_lock<std::mutex>& lck);
  public:
    void route(ClientMessage& msg);
    Queue<ClientMessage>& get_c2s_queue();
    void broadcast(int gameID, GameState msg);
    int add_client(std::shared_ptr<Queue<GameState>> queue);
    void remove_client(int clientID);
    void quit_client(int clientID);
    void closeGame(int gameID);
    void pushCommand(std::string cmd);
    void stop();
    void join();
    void reap();
    void exitClients(int gameID);
};

#endif
