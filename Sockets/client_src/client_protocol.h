//
// Created by tom on 30/03/24.
//

#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <arpa/inet.h>

#include "../common_src/defs.h"
#include "../common_src/socket.h"

class ClientProtocol {
private:
    Socket socket;
    std::vector<Action> encode_actions_line(std::string& line);

public:
    ClientProtocol(const char* hostname, const char* port);
    void send_message(std::string line);
    std::string receive_message();
    ~ClientProtocol() = default;
};

#endif  // CLIENT_PROTOCOL_H
