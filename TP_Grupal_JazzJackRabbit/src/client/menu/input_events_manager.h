#ifndef EVENTS_MANAGER_H
#define EVENTS_MANAGER_H

#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;

class InputEventsManager
{
private:
public:
    void events(SDL_Event event, int &position, std::string &text);
};

#endif