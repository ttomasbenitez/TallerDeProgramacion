#ifndef RECEIVER_H
#define RECEIVER_H

#include <iostream>

#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "clients_queues_monitor.h"
#include "server_protocol.h"

class Receiver: public Thread {
private:
    ServerProtocol& protocol;
    Queue<enum Command>& game_commands;

public:
    Receiver(ServerProtocol& server_protocol, Queue<enum Command>& commands);
    void receive_message();
    void run() override;
    void stop() override;
    ~Receiver() = default;
};


#endif  // RECEIVER_H
