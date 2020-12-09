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

#endif
