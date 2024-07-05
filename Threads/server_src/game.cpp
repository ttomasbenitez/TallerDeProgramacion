//
// Created by tom on 10/04/24.
//

#include "game.h"

Game::Game(ClientsQueuesMonitor& monitor, Queue<enum Command>& commands):
        monitor(monitor), client_commands(commands), alive_enemies(5), dead_enemies(0) {}

void Game::revive_enemy() {
    alive_enemies++;
    dead_enemies--;
}
void Game::receive_attack() {
    alive_enemies--;
    dead_enemies++;
}

void Game::stop() {
    _is_alive = false;
    _keep_running = false;
}

void Game::print_and_broadcast_info(uint8_t event_type) {
    GameInfo game_info(alive_enemies, dead_enemies, event_type);
    game_info.print_info();
    monitor.broadcast(game_info);
}

void Game::run() {

    std::vector<Enemy> enemies(NUMBER_OF_ENEMIES);
    while (this->_keep_running) {


        Command command;
        if (client_commands.try_pop(command) && command == ATACAR_CMD && alive_enemies > 0) {
            receive_attack();
            print_and_broadcast_info(DEAD_ENEMY);

            for (auto& enemy: enemies) {
                if (enemy.is_alive()) {
                    enemy.receive_attack();
                    break;
                }
            }
        }

        for (auto& enemy: enemies) {

            if (!enemy.is_alive()) {
                if (enemy.revive()) {
                    revive_enemy();
                    print_and_broadcast_info(REVIVED_ENEMY);
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
