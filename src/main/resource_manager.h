#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <unordered_map>

#include "resource.h"
#include "sdl/image.h"
#include "sdl/window.h"

class ResourceManager {
 private:
  std::unordered_map<int, Resource> resources;
  Window& window;

 public:
  ResourceManager(Window& window);
  ~ResourceManager();

  Image* get_image(int id);
};

ResourceManager::ResourceManager(Window& window) : window(window) {}

ResourceManager::~ResourceManager() {}

Image* ResourceManager::get_image(int id) {
  if (resources.find(id) == resources.end()) {
    throw 1;  // TODO Throw KeyError
  }
  Resource& res = resources[id];
  if (!res.is_loaded()) {
    res.load(window.get_renderer());
  }
  return res.get_image();
}

#endif
