#ifndef __MENU_OPTIONS_H__
#define __MENU_OPTIONS_H__

#include <SDL2pp/SDL2pp.hh>
using namespace SDL2pp;
#include <vector>
#include "../renderer_manager/renderer_manager.h"
#include "music_manager/music_manager.h"
#include "../game_information.h"
#include <vector>
#include <list>
#include "queue.h"
#include "clientaction.h"
#include "gamestate.h"

class MenuOptionsManager
{
protected:
    RendererManager *rendererManager;
    MusicManager *musicManager;
    std::vector<Rect> buttons;
    void show(std::vector<std::string> options, std::vector<SDL_Color> mainColors);
    void createMenu(std::vector<std::string> options, std::vector<SDL_Color> mainColors);

public:
    MenuOptionsManager(RendererManager *rendererManager, MusicManager *musicManager);
};

#endif