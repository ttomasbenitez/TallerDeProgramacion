//
// Created by tom on 10/04/24.
//

#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include "../common_src/game_info.h"

#include "client_protocol.h"

#define STR_ATACAR "Atacar"
#define STR_LEER "Leer"
#define STR_SALIR "Salir"


class Client {
private:
    ClientProtocol protocol;
    bool finish_communication;
    void receive_message(const std::string& message_count);
    void process_action(std::string& line);

public:
    Client(const char* hostname, const char* port);
    void run();
    ~Client() = default;
};


#endif  // CLIENT_H
