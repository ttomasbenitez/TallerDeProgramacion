//
// Created by tom on 31/03/24.
//

#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <atomic>
#include <iostream>
#include <utility>

#include <arpa/inet.h>

#include "../common_src/defs.h"
#include "../common_src/game_info.h"
#include "../common_src/socket.h"


class ServerProtocol {
private:
    Socket socket;
    std::atomic<bool> was_closed;
    enum Command decode_received_command(const uint8_t& received_command);

public:
    explicit ServerProtocol(Socket& socket);
    void send_message(GameInfo& message_info);
    enum Command receive_command();
    bool skt_was_closed();
    ~ServerProtocol() = default;
};


#endif  // SERVER_PROTOCOL_H
