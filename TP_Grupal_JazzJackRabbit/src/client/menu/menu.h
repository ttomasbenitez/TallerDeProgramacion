#ifndef __MENU_H__
#define __MENU_H__

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
#include "menu_options_manager.h"

class Menu : public MenuOptionsManager
{
private:
    Queue<ClientAction> &actionQueue;
    Queue<GameState> &responseQueue;

    void events(bool &hasClosed, gameInformation &game, Window *window);
    bool joinCreateMenu(gameInformation &game, Window *window, bool &hasClosed);
    int chooseCharacter();
    int editLevels(Window *window);
    bool isEditing;

public:
    Menu(RendererManager *rendererManager, MusicManager *musicManager, Queue<ClientAction> &actionQueue, Queue<GameState> &responseQueue);
    void initMenu(gameInformation &game, Window *window);
};

#endif