#ifndef SERVER_H
#define SERVER_H

#include <string>
#include "config.h"
#include "gamelogic/gamemanager.h"
#include "net/acceptor.h"

class Server {
private:
    GameManager games;
    Acceptor acceptor;
public:
    Server();
    void start();
};

#endif
