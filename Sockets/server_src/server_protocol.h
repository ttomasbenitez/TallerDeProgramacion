//
// Created by tom on 31/03/24.
//

#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <arpa/inet.h>

#include "../common_src/defs.h"
#include "../common_src/socket.h"


class ServerProtocol {
private:
    Socket socket;

public:
    explicit ServerProtocol(Socket& socket);
    std::vector<uint8_t> receive_line(bool* was_closed);
    std::vector<std::string> decode_received_line(uint8_t* data, int number_received);
    void send_received_line(const std::string& line, bool* was_closed);
    ~ServerProtocol() = default;
};


#endif  // SERVER_PROTOCOL_H
