#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <unordered_map>

#include "resource.h"
#include "sdl/image.h"

class ResourceManager {
 private:
  std::unordered_map<int, Resource> resources;

 public:
  ResourceManager();
  ~ResourceManager();

  Image* get_image(int id);
};

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager() {}

Image* ResourceManager::get_image(int id) {
  if (resources.find(id) == resources.end()) {
    throw 1;  // TODO Throw KeyError
  }
  Resource& res = resources[id];
  if (!res.is_loaded()) {
    res.load();
  }
  return res.get_image();
}

#endif
