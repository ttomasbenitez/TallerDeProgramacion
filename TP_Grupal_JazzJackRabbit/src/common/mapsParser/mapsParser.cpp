#include "mapsParser.h"

MapsParser::MapsParser(const char *filename) : mapsNode(YAML::LoadFile(filename)) {}

mapData MapsParser::loadMap(YAML::Node e)
{
    mapData map;
    map.path = e["path"].as<std::string>();
    map.name = e["name"].as<std::string>();
    return map;
}

void MapsParser::getMaps(std::vector<mapData> &maps)
{
    for (size_t i = 0; i < mapsNode["maps"].size(); i++)
    {
        maps.push_back(this->loadMap(mapsNode["maps"][i]));
    }
}

void MapsParser::addNewMap(const std::string filePath, const std::string mapName)
{
    YAML::Node map;
    map["path"] = filePath;
    map["name"] = mapName;

    if (mapsNode["maps"].size() == 0)
    {
        mapsNode['maps'] = map;
    }
    else
    {
        mapsNode["maps"].push_back(map);
    }

    std::ofstream fout(DYAML_ARCHIVES "/maps.yaml");
    fout << mapsNode;
}