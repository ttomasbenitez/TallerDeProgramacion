#include "element_reader.h"

ElementReader::ElementReader(const char *filename) : element(YAML::LoadFile(filename)) {}

void ElementReader::loadElements(std::vector<Item> &itemList)
{
  for (size_t i = 0; i < element["elements"].size(); i++)
  {
    itemList.push_back(this->loadElement(element["elements"][i]));
  }
}

Item ElementReader::loadElement(YAML::Node e)
{
  Item item;
  item.type = e["type"].as<std::string>();
  item.id = e["id"].as<int>();
  return item;
}

Item ElementReader::getBackground()
{
  Item item;
  item.id = element["background"].as<int>();
  item.type = "background";
  return item;
}
