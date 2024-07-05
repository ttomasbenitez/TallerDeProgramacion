#ifndef MAPS_PARSER_H
#define MAPS_PARSER_H

#include "map.h"
#include <vector>
#include <yaml-cpp/yaml.h>
#include <fstream>

class MapsParser
{
private:
    YAML::Node mapsNode;
    mapData loadMap(YAML::Node e);

public:
    MapsParser(const char *filename);
    void getMaps(std::vector<mapData> &maps);
    void addNewMap(const std::string filePath, const std::string mapName);
};
#endif