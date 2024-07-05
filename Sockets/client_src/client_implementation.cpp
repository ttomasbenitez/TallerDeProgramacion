//
// Created by tom on 10/04/24.
//

#include "client_implementation.h"

Client::Client(const char* hostname, const char* port): protocol(hostname, port) {}

void Client::run() {

    std::string line;
    while (std::getline(std::cin, line)) {
        protocol.send_message(line);
        std::string response = protocol.receive_message();
        std::cout << response << std::endl;
    }
}
