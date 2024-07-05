#ifndef CLIENT_IO_HANDLER_H
#define CLIENT_IO_HANDLER_H

#include "thread.h"
#include "queue.h"
#include "clientaction.h"
#include "gamestate.h"
#include "socket.h"
#include "clientsendhandler.h"
#include "clientrecvhandler.h"
#include "gamelogic/gamemanager.h"

class ClientIOHandler: public Runnable {
  private:
    int id;
    Socket sock;
    std::shared_ptr<Queue<GameState>> s2c_queue;
    GameManager& game_manager;
    ClientSendHandler send;
    ClientRecvHandler recv;
  public:
    explicit ClientIOHandler(int id, Socket sock, std::shared_ptr<Queue<GameState>> s2c, GameManager& game_manager);
    void start() override;
    void stop() override;
    void join() override;
    bool is_alive() const override;
    int get_id();
};

#endif
