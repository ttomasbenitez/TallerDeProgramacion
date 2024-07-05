#ifndef DEFS_H
#define DEFS_H

#include <cstdint>

enum Action : uint8_t {
    NOP = 0x00,
    JUMP = 0x01,
    RIGHT = 0x02,
    LEFT = 0x03,
    DUCK = 0x04,
    HIT = 0x05
};

#define ACTION_JUMP "JUMP"
#define ACTION_RIGHT "RIGHT"
#define ACTION_LEFT "LEFT"
#define ACTION_DUCK "DUCK"
#define ACTION_HIT "HIT"
#define ACTION_SIDEKICK "SIDEKICK"
#define ACTION_UPPERCUT "UPPERCUT"
#define ACTION_HIGHKICK "HIGHKICK"

#define UNKNOWN_ACTION_ERR "Unknown action."

#endif  // DEFS_H
