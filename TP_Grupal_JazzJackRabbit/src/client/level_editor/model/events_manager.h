#ifndef EVENTS_MANAGER_H
#define EVENTS_MANAGER_H

#include <list>
#include <memory>
#include <vector>
#include <string>
#include <SDL2pp/SDL2pp.hh>
#include "../../renderer_manager/renderer_manager.h"
#include "level_entities.h"
#include "camera.h"
#include "level_parser.h"
#include "palette/palette.h"

using namespace SDL2pp;

class EventsManager
{
private:
    LevelData *level;
    Palette *palette;
    Camera *camera;
    int *x;
    int *y;
    int *selectedEntityID;

    void chooseNewEntity();
    void scroll(bool &scrool, int &scrollSpeed, int speed);
    void saveGame(int &opacity, std::string &buttonPath, std::string filename);
    int getSelectedEntityID();
    bool inPalette();

public:
    EventsManager(LevelData *level, int *x, int *y, int *selectedEntityID, Camera *camera, Palette *palette);
    void mouseButtonDown(bool &scrool, int &scrollSpeed, bool &quit, int &n, int &opacity, std::string &buttonPath, std::string filename);
    void keyDown(SDL_Event event, bool &quit);
    void windowsEvent(SDL_Event event, int &n, bool &quit);
    void dragSelectedEntity();
};

#endif