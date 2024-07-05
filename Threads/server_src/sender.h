#ifndef SENDER_H
#define SENDER_H

#include <iostream>

#include <syslog.h>

#include "../common_src/game_info.h"
#include "../common_src/queue.h"
#include "../common_src/socket.h"
#include "../common_src/thread.h"

#include "clients_queues_monitor.h"
#include "receiver.h"
#include "server_protocol.h"

class Sender: public Thread {
private:
    ServerProtocol protocol;
    ClientsQueuesMonitor& monitor;
    Queue<enum Command>& game_commands;
    Queue<GameInfo> messages_to_send;

public:
    Sender(Socket& client_socket, ClientsQueuesMonitor& clients_monitor,
           Queue<enum Command>& commands);
    void send_message(GameInfo& message);
    void stop() override;
    void run() override;
    ~Sender() = default;
};


#endif  // SENDER_H
