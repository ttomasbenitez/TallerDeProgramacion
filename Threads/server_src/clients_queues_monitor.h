#ifndef CLIENT_QUEUES_MONITOR_H
#define CLIENT_QUEUES_MONITOR_H

#include <iostream>
#include <map>
#include <mutex>

#include "../common_src/defs.h"
#include "../common_src/game_info.h"
#include "../common_src/queue.h"

class ClientsQueuesMonitor {
private:
    std::mutex map_mtx;
    std::map<int, Queue<GameInfo>*> clients_queues;

public:
    ClientsQueuesMonitor();
    int add_client_queue(Queue<GameInfo>& client_queue);
    void broadcast(const GameInfo& info);
    void remove_client_queue(int& index);
    ~ClientsQueuesMonitor() = default;
};


#endif  // CLIENT_QUEUES_MONITOR_H
