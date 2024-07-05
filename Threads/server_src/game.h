//
// Created by tom on 10/04/24.
//

#ifndef GAME_H
#define GAME_H

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "../common_src/defs.h"
#include "../common_src/game_info.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "clients_queues_monitor.h"
#include "enemy.h"

#define NUMBER_OF_ENEMIES 5

class Game: public Thread {
private:
    ClientsQueuesMonitor& monitor;
    Queue<enum Command>& client_commands;
    int alive_enemies;
    int dead_enemies;
    void revive_enemy();
    void receive_attack();
    void print_and_broadcast_info(uint8_t event_type);

public:
    Game(ClientsQueuesMonitor& monitor, Queue<enum Command>& commands);
    void run() override;
    void stop() override;
    ~Game() = default;
};


#endif  // GAME_H
