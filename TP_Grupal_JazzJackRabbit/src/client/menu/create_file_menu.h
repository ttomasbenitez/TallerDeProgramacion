#ifndef CREATE_FILE__MENU_H__
#define CREATE_FILE__MENU_H__
#include <SDL2pp/SDL2pp.hh>
using namespace SDL2pp;
#include "../renderer_manager/renderer_manager.h"
#include "music_manager/music_manager.h"
struct Input
{
    std::string name;
    bool isSelected;
    int position;
};
class CreateFileMenu
{
private:
    RendererManager *rendererManager;
    MusicManager *musicManager;
    std::vector<Input> inputs;
    int selected;
    int events(bool &hasClosed);
    void showOptions(bool showCursor);

public:
    CreateFileMenu(RendererManager *rendererManager, MusicManager *musicManager);
    std::pair<int, std::pair<std::string, std::string>> initMenu();
};
#endif