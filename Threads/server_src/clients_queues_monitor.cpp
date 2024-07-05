//
// Created by tom on 23/04/24.
//

#include "clients_queues_monitor.h"

ClientsQueuesMonitor::ClientsQueuesMonitor() {}

int ClientsQueuesMonitor::add_client_queue(Queue<GameInfo>& client_queue) {
    std::lock_guard<std::mutex> lck(map_mtx);

    int index = clients_queues.size();
    clients_queues[index] = &client_queue;

    return index;
}

void ClientsQueuesMonitor::broadcast(const GameInfo& info) {
    std::lock_guard<std::mutex> lck(map_mtx);

    for (auto it = clients_queues.begin(); it != clients_queues.end(); ++it) {
        it->second->push(info);
    }
}

void ClientsQueuesMonitor::remove_client_queue(int& index) {
    std::lock_guard<std::mutex> lck(map_mtx);

    clients_queues.erase(index);
}
