//
// Created by tom on 10/04/24.
//

#ifndef SERVER_IMPLEMENTATION_H
#define SERVER_IMPLEMENTATION_H

#include <iostream>

#include "../common_src/socket.h"

#include "acceptor.h"

#define QUIT 'q'

class Server {
private:
    Socket socket;

public:
    explicit Server(const char* port);
    void run();
    ~Server() = default;
};


#endif  // SERVER_IMPLEMENTATION_H
