#ifndef CONFIG_H
#define CONFIG_H

#include <yaml-cpp/yaml.h>
#include <sstream>

class Config {
private:
  const YAML::Node config;
public:
    explicit Config(const char* filename): config(YAML::LoadFile(filename)) {}
    template<typename T>
    T get(const char* key) const {
      auto node = this->findNode(key, this->config);
      return node.as<T>();
    }
    YAML::Node findNode(std::string key, YAML::Node node) const {
      auto pos = key.find(".");
      if (pos == std::string::npos) return node[key];
      std::string lkey = key.substr(0, pos);
      std::string rest = key.substr(pos + 1, key.length());
      return this->findNode(rest, node[lkey]);
    }
};

extern Config config;

#endif
