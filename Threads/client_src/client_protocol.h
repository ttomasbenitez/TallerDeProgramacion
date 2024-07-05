//
// Created by tom on 30/03/24.
//

#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <iostream>

#include <arpa/inet.h>

#include "../common_src/defs.h"
#include "../common_src/game_info.h"
#include "../common_src/socket.h"

class ClientProtocol {
private:
    Socket socket;

public:
    ClientProtocol(const char* hostname, const char* port);
    void send_attack_message();
    GameInfo receive_message();
    ~ClientProtocol() = default;
};

#endif  // CLIENT_PROTOCOL_H
