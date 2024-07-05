//
// Created by tom on 10/04/24.
//

#include "game_logic.h"

GameLogic::GameLogic(): performed_actions(0) {}

int GameLogic::get_performed_actions() const { return performed_actions; }

std::string GameLogic::filter_combos(std::string* received_actions, int received_number) {
    std::string game_moves = "";

    for (int i = 0; i < received_number; i++) {

        if (received_actions[i].compare(ACTION_JUMP) == 0) {
            if (i + 2 < received_number && received_actions[i + 1].compare(ACTION_JUMP) == 0 &&
                received_actions[i + 2].compare(ACTION_HIT) == 0) {

                game_moves += ACTION_UPPERCUT;
                i += 2;
            } else {
                game_moves += ACTION_JUMP;
            }
        } else if (received_actions[i].compare(ACTION_RIGHT) == 0) {
            game_moves += ACTION_RIGHT;
        } else if (received_actions[i].compare(ACTION_LEFT) == 0) {

            if (i + 3 < received_number && received_actions[i + 1].compare(ACTION_RIGHT) == 0 &&
                received_actions[i + 2].compare(ACTION_JUMP) == 0 &&
                received_actions[i + 3].compare(ACTION_HIT) == 0) {

                game_moves += ACTION_HIGHKICK;
                i += 3;
            } else {
                game_moves += ACTION_LEFT;
            }
        } else if (received_actions[i].compare(ACTION_DUCK) == 0) {
            game_moves += ACTION_DUCK;
        } else if (received_actions[i].compare(ACTION_HIT) == 0) {
            if (i + 2 < received_number && received_actions[i + 1].compare(ACTION_DUCK) == 0 &&
                received_actions[i + 2].compare(ACTION_LEFT) == 0) {
                game_moves += ACTION_SIDEKICK;
                i += 2;
            } else {
                game_moves += ACTION_HIT;
            }
        } else {
            std::cerr << UNKNOWN_ACTION_ERR << std::endl;
        }
        game_moves += " ";
        performed_actions++;
    }

    game_moves.pop_back();
    return game_moves;
}
