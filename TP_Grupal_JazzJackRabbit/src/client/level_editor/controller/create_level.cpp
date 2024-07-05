#include "create_level.h"
#include "../../../common/mapsParser/mapsParser.h"

CreateLevel::CreateLevel(RendererManager *rendererManager, int scenery, std::string mapName, std::string filename) : CommonEditor(rendererManager, scenery, filename)
{
    level.scenery = scenery;
    this->mapName = mapName;
}

int CreateLevel::run()
{
    level.background = (int)(AnimationState::EMPTY_BACKGROUND);
    MapsParser mapsParser(DYAML_ARCHIVES "/maps.yaml");
    mapsParser.addNewMap(filename, mapName);
    filename = DYAML_ARCHIVES + filename;
    return selectEntityToEdit();
}
