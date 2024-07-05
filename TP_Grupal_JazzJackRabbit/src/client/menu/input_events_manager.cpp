#include "input_events_manager.h"

void InputEventsManager::events(SDL_Event event, int &position, std::string &text)
{

    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:

            if (position > 0)
            {
                position -= 1;
            }
            break;
        case SDLK_RIGHT:
            if (text.size() > position)
            {
                position += 1;
            }
            break;
        case SDLK_BACKSPACE:
            if (position >= 1)
            {
                text.erase(position - 1, 1);
                position--;
            }
            break;
        default:
            break;
        }
    }
    else if (event.type == SDL_TEXTINPUT)
    {
        if (position != text.size())
        {
            text.insert(position, event.text.text);
        }
        else
        {
            text += event.text.text;
        }
        position += strlen(event.text.text);
    }
}