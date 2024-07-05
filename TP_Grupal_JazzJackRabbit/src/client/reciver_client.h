#ifndef __RECIVER_CLIENT_H__
#define __RECIVER_CLIENT_H__

#include "queue.h"
#include "client_protocol.h"
#include "thread.h"
#include "gamestate.h"

class Client;
class Reciver : public Thread
{
private:
    Queue<GameState>& responseQueue;
    Protocol& protocol;
    Client& client;
public:
    Reciver(Queue<GameState>& queue, Protocol& protocol, Client& client);
    void run() override;
    void stop() override;
    ~Reciver() {}
};


#endif