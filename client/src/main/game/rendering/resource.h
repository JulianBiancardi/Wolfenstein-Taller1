#ifndef RESOURCE_H
#define RESOURCE_H

#include <SDL2/SDL.h>

#include "sdl/image.h"

class Resource {
 private:
  bool loaded;
  int id;
  Image* image;

 public:
  Resource();
  explicit Resource(int id);
  ~Resource();

  bool is_loaded();
  void load(SDL_Renderer* renderer);
  Image* get_image();
};

#endif
