#include "game_info.h"

GameInfo::GameInfo(int alive, int dead, uint8_t event):
        alive_enemies(alive), dead_enemies(dead), event_type(event) {}

void GameInfo::print_info() {
    std::cout << get_event_message(alive_enemies, dead_enemies, event_type) << std::endl;
}

int GameInfo::get_alive_enemies() { return alive_enemies; }

int GameInfo::get_dead_enemies() { return dead_enemies; }

uint8_t GameInfo::get_event_type() { return event_type; }
