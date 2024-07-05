#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "thread.h"
#include "socket.h"
#include "gamelogic/gamemanager.h"
#include "net/clientiohandler.h"
#include "queue.h"
#include "clientaction.h"
#include <list>
#include <optional>

class Acceptor: public Thread {
  private:
    Socket sock;
    GameManager& games;
    std::list<std::unique_ptr<ClientIOHandler>> clients;

    std::optional<Socket> accept();
    void reap();
  public:
    explicit Acceptor(Socket sock, GameManager& games);
    void stop() override;
    void run() override;
    ~Acceptor() {}
};

#endif
