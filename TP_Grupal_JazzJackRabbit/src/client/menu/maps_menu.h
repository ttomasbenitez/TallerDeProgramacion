#ifndef MAPS__MENU_LEVEL_H__
#define MAPS__MENU_LEVEL_H__

#include <SDL2pp/SDL2pp.hh>
using namespace SDL2pp;
#include <vector>
#include "../renderer_manager/renderer_manager.h"
#include "music_manager/music_manager.h"

struct mapElement
{
    std::string path;
    std::string name;
    int posY;
    int width;
    int height;
};

class MapsMenu
{
private:
    RendererManager *rendererManager;
    MusicManager *musicManager;
    std::vector<mapElement> mapElements;
    int cameraY;

    std::string events();
    std::string selectMap(int mouseX, int mouseY);
    void showMenuGames();
    void setCameraPos(int scrollSpeed);

public:
    MapsMenu(RendererManager *rendererManager, MusicManager *musicManager);
    std::string initMenu();
};

#endif