#ifndef LEVEL_EDIT_H
#define LEVEL_EDIT_H

#include <list>
#include <memory>
#include "../../renderer_manager/renderer_manager.h"
#include "common_editor.h"

#include <SDL2pp/SDL2pp.hh>
using namespace SDL2pp;

class LevelEdit : public CommonEditor
{
private:
    LevelParser *parser;

public:
    int run();
    LevelEdit(RendererManager *rendererManager, LevelParser *parser, std::string filename);
};

#endif