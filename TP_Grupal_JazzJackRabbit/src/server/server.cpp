#include "server.h"
#include "socket.h"
#include "config.h"

#include <string>
#include <iostream>

Server::Server(): games(),
                  acceptor(
                    Socket(
                      config.get<std::string>("listen_port").c_str()
                    ),
                    games
                  ) {}

void Server::start() {
    acceptor.start();
    for (std::string line; std::getline(std::cin, line);) {
        if (line == "q")
            break;
        games.pushCommand(line);
    }
    acceptor.stop();
    games.stop();
    acceptor.join();
    games.join();
}
