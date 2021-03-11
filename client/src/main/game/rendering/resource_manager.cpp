#include "resource_manager.h"

#include "../../../../../common/src/main/paths.h"
#include "yaml-cpp/yaml.h"

ResourceManager::ResourceManager(Window& window) : window(window) {
  YAML::Node yaml_file = YAML::LoadFile(config_path("ids.yaml"));

  YAML::const_iterator iter;
  for (iter = yaml_file.begin(); iter != yaml_file.end(); iter++) {
    int id = iter->first.as<int>();
    resources[id] = Resource(id);
  }
}

ResourceManager::~ResourceManager() {}

Image* ResourceManager::get_image(int id) {
  Resource& res = resources.at(id);
  if (!res.is_loaded()) {
    res.load(window.get_renderer());
  }
  return res.get_image();
}