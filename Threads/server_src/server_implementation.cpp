//
// Created by tom on 10/04/24.
//

#include "server_implementation.h"

Server::Server(const char* port): socket(port) {}

void Server::run() {

    Acceptor acceptor(socket);
    acceptor.start();

    char input;
    std::cin >> input;
    while (input != QUIT) {}
    acceptor.stop();
    acceptor.join();
}
