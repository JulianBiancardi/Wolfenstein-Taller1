#include "resource.h"

#include <map>
#include <string>

#include "yaml-cpp/yaml.h"

Resource::Resource() : id(-1), loaded(false), image(NULL) {}

Resource::Resource(int id) : id(id), loaded(false), image(NULL) {}

Resource::~Resource() {
  if (loaded) {
    delete image;
  }
}

bool Resource::is_loaded() { return loaded; }

// Use the YAML to find the relevant data
// TODO Fix this
void Resource::load(SDL_Renderer* renderer) {
  YAML::Node yaml_file = YAML::LoadFile("../common/ids.yaml");

  std::map<std::string, std::string> resource_data =
      yaml_file[id].as<std::map<std::string, std::string>>();

  std::map<std::string, std::string>::iterator iter;
  for (iter = resource_data.begin(); iter != resource_data.end(); iter++) {
    std::string key = iter->first;
    std::string value = iter->second;
    if (key == "image") {
      image = new Image(renderer, value);
    }
  }

  loaded = true;
}

Image* Resource::get_image() { return image; }