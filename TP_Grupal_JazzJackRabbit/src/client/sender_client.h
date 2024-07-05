#ifndef __SENDER_CLIENT_H__
#define __SENDER_CLIENT_H__

#include "thread.h"
#include "queue.h"
#include "client_protocol.h"
#include "clientaction.h"

class Client;

class Sender: public Thread
{
private:
   Queue<ClientAction>& actionQueue;
   Protocol& protocol;
   Client& client;
public:
    Sender(Queue<ClientAction>& queue, Protocol& protocol, Client& client);
    void run() override;
    bool is_running();
    void stop() override;
    ~Sender() {}
};

#endif
