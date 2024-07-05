#ifndef __PROTOCOL_CLIENT_H__
#define __PROTOCOL_CLIENT_H__

#include "socket.h"
#include "clientaction.h"
#include "gamestate.h"
#include <string>

class Protocol
{
private:
    Socket skt;
    bool was_close;
public:
    Protocol(const std::string& hostname, const std::string& servname);
    void send(ClientAction action);
    void close();
    GameState recive();
    bool is_close();

    ~Protocol() {}
};


#endif