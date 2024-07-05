#ifndef COMMON_EDITOR_H
#define COMMON_EDITOR_H

#include <list>
#include <memory>
#include <vector>
#include <string>
#include <SDL2pp/SDL2pp.hh>
#include "../../renderer_manager/renderer_manager.h"
#include "../model/level_entities.h"
#include "../model/camera.h"
#include "../model/level_parser.h"
#include "../model/palette/palette.h"
#include <utility> // std::pair, std::make_pair

#define CAMERA_SPEED 10
#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 480

using namespace SDL2pp;

class CommonEditor
{
protected:
    RendererManager *rendererManager;
    Camera camera;
    Palette palette;
    LevelData level;
    std::string filename;

public:
    void initCommonEditor();
    CommonEditor(RendererManager *rendererManager, int scenery, std::string filename);
    virtual int run() = 0;
    int selectEntityToEdit();
    ~CommonEditor() = default;
};

#endif