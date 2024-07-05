#ifndef GRAPHICS_LEVEL_EDITOR_H
#define GRAPHICS_LEVEL_EDITOR_H

#include <map>
#include <SDL2pp/SDL2pp.hh>
#include "../../renderer_manager/renderer_manager.h"
#include "../model/camera.h"
#include "../model/level_entities.h"
#include "../model/palette/palette.h"

using namespace SDL2pp;

class GraphicsLevelEditor
{
private:
    RendererManager *rendererManager;
    void renderEntities(LevelData level, Camera camera);
    void renderButtons();
    void renderNotifications(int &opacity, std::string buttonPath);
    void renderBackground(int backgroundID);

public:
    GraphicsLevelEditor(RendererManager *rendererManager);
    void renderLevel(int &opacity, std::string buttonPath, Camera camera, LevelData level, Palette *palette);
};

#endif