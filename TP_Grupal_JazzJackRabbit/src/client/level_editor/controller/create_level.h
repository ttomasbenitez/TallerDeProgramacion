#ifndef CREATE_LEVEL_H
#define CREATE_LEVEL_H

#include <list>
#include <memory>
#include "../../renderer_manager/renderer_manager.h"
#include "common_editor.h"

#include <SDL2pp/SDL2pp.hh>
using namespace SDL2pp;

class CreateLevel : public CommonEditor
{
private:
    std::string mapName;

public:
    int run();
    CreateLevel(RendererManager *rendererManager, int scenery, std::string mapName, std::string filename);
};

#endif