#ifndef USER_NAME_MENU_H__
#define USER_NAME_MENU_H__
#include <SDL2pp/SDL2pp.hh>
using namespace SDL2pp;
#include "../renderer_manager/renderer_manager.h"
#include "music_manager/music_manager.h"

class UserNameMenu
{
private:
    RendererManager *rendererManager;
    MusicManager *musicManager;
    std::string name;
    int position;
    int events(bool &hasClosed);
    void showOptions(bool showCursor);

public:
    UserNameMenu(RendererManager *rendererManager, MusicManager *musicManager);
    std::pair<int, std::string> initUserNameMenu();
};
#endif