#ifndef ELEMENT_READER_H
#define ELEMENT_READER_H

#include <yaml-cpp/yaml.h>
#include <vector>
#include <memory>
#include "../item.h"

class ElementReader
{
private:
    YAML::Node element;
    Item loadElement(YAML::Node e);

public:
    explicit ElementReader(const char *filename);
    void loadElements(std::vector<Item> &itemList);
    Item getBackground();
    Item getPlayer();
};

#endif
