#ifndef PALETTE_H
#define PALETTE_H

#include <string>
#include <SDL2pp/SDL.hh>
#include "../../../renderer_manager/renderer_manager.h"
#include "../item.h"
#include <vector>
#include <utility> // std::pair, std::make_pair

using namespace SDL2pp;

struct Element
{
    std::string type;
    int id;
    int posX;
    int posY;
    //  Texture texture;
};

class Palette
{
private:
    std::vector<Element> palette;
    RendererManager *rendererManager;
    std::vector<Texture*> sprites;
    int cameraY;
    int scrollPos;
    std::vector<Item> readItems(int numbOfScenery);

public:
    Palette(RendererManager *rendererManager, int numbOfScenery);
    void showPalette();
    std::pair<int, std::string> selectEntity(int mouseX, int mouseY);
    void updatePosition(int scrollY);
};
#endif
