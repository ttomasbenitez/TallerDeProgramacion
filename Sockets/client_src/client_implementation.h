//
// Created by tom on 10/04/24.
//

#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include "client_protocol.h"


class Client {
private:
    ClientProtocol protocol;

public:
    Client(const char* hostname, const char* port);
    void run();
    ~Client() = default;
};


#endif  // CLIENT_H
