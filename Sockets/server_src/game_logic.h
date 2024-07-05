//
// Created by tom on 10/04/24.
//

#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <iostream>
#include <string>

#include "../common_src/defs.h"

class GameLogic {
private:
    int performed_actions;

public:
    GameLogic();
    std::string filter_combos(std::string* received_actions, int received_number);
    int get_performed_actions() const;
    ~GameLogic() = default;
};


#endif  // GAME_LOGIC_H
