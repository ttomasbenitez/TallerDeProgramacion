#ifndef DEFS_H
#define DEFS_H

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

#define MAX_SIZE 32
#define UNKNOWN_COMMAND_ERR "Unknown command received."


enum ProtocolEncoding : uint8_t {
    ATTACK = 0x03,
    DEAD_ENEMY = 0x04,
    REVIVED_ENEMY = 0x05,
    MESS_START = 0x06,
};


enum Command {
    ERROR,
    ATACAR_CMD,
};


std::string get_event_message(const int& alive_enemies, const int& dead_enemies,
                              const uint8_t& event_type);


#endif  // DEFS_H
