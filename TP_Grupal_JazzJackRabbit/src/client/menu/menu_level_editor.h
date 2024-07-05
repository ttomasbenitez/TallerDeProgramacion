#ifndef __MENU_LEVEL_H__
#define __MENU_LEVEL_H__

#include <SDL2pp/SDL2pp.hh>
using namespace SDL2pp;
#include <vector>
#include "../game_information.h"
#include <vector>
#include <list>
#include "menu_options_manager.h"
#include "../level_editor/model/item.h"

class MenuLevelEditor : public MenuOptionsManager
{
private:
    Window *window;
    int events(bool &hasClosed);
    void editLevels(bool &hasClosed);
    void createLevels(bool &hasClosed);
    void returnToMenu();
    void checkHasClosed(int n, bool &hasClosed);

public:
    MenuLevelEditor(RendererManager *rendererManager, MusicManager *musicManager);
    int initMenu(Window *window);
};

#endif