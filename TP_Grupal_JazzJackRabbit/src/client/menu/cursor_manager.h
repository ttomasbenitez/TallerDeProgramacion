#ifndef CURSOR_MANAGER_H
#define CURSOR_MANAGER_H

#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;

class CursorManager
{
private:
    int lastBlinkTime;
    const int blinkInterval;

public:
    CursorManager(const int blinkInterval);
    void shouldBlink(bool &showCursor);
};

#endif