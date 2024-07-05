//
// Created by tom on 10/04/24.
//

#ifndef SERVER_IMPLEMENTATION_H
#define SERVER_IMPLEMENTATION_H

#include <iostream>
#include <string>
#include <vector>

#include "../common_src/socket.h"

#include "game_logic.h"
#include "server_protocol.h"

class Server {
private:
    Socket socket;

public:
    explicit Server(const char* port);
    void run();
    ~Server() = default;
};


#endif  // SERVER_IMPLEMENTATION_H
