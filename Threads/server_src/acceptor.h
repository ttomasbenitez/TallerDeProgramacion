#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <iostream>
#include <list>
#include <utility>

#include <arpa/inet.h>
#include <syslog.h>

#include "../common_src/queue.h"
#include "../common_src/socket.h"
#include "../common_src/thread.h"

#include "clients_queues_monitor.h"
#include "game.h"
#include "sender.h"


class Acceptor: public Thread {
private:
    Socket socket;
    ClientsQueuesMonitor monitor;
    Queue<enum Command> game_commands;
    std::list<Sender*> senders;
    void reap_dead();
    void connect_client(Socket& client_socket);
    void kill_all();

public:
    explicit Acceptor(Socket& acceptor_skt);
    void run() override;
    void stop() override;
    ~Acceptor() = default;
};


#endif  // ACCEPTOR_H
