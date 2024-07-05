#include "level_edit.h"
#include "../model/level_parser.h"

LevelEdit::LevelEdit(RendererManager *rendererManager, LevelParser *parser, std::string filename) : CommonEditor(rendererManager, parser->getScenery(), filename)
{
    this->parser = parser;
}

int LevelEdit::run()
{

    level = parser->readLevelData();
    return selectEntityToEdit();
}
