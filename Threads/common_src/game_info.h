#ifndef GAME_INFO_H
#define GAME_INFO_H

#include <cstdint>
#include <iostream>

#include "defs.h"

class GameInfo {
private:
    int alive_enemies;
    int dead_enemies;
    uint8_t event_type;

public:
    GameInfo(int alive, int dead, uint8_t event);
    int get_alive_enemies();
    int get_dead_enemies();
    uint8_t get_event_type();
    void print_info();
    ~GameInfo() = default;
};


#endif  // GAME_INFO_H
