#ifndef __JOIN_MENU_H__
#define __JOIN_MENU_H__

#include <SDL2pp/SDL2pp.hh>
using namespace SDL2pp;
#include <vector>
#include "../renderer_manager/renderer_manager.h"
#include "../game_information.h"
#include <vector>
#include <list>
#include "queue.h"
#include "clientaction.h"
#include "gamestate.h"

class JoinMenu
{
private:
    RendererManager *rendererManager;
    Queue<ClientAction> &actionQueue;
    Queue<GameState> &responseQueue;
    int event(bool &finished, int &page, int n, std::vector<Rect> buttons);
    void loading();

public:
    JoinMenu(RendererManager *rendererManager, Queue<ClientAction> &actionQueue, Queue<GameState> &responseQueue);
    int join();
};

#endif