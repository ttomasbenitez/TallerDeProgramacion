#include "cursor_manager.h"
CursorManager::CursorManager(const int blinkInterval) : blinkInterval(blinkInterval)
{
    lastBlinkTime = SDL_GetTicks();
}

void CursorManager::shouldBlink(bool &showCursor)
{
    int currentTime = SDL_GetTicks();
    int elapsedTime = currentTime - lastBlinkTime;

    if (elapsedTime >= blinkInterval)
    {
        showCursor = !showCursor;
        lastBlinkTime = currentTime;
    }
}
