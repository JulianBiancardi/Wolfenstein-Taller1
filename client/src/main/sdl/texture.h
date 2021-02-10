#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>

#include "surface.h"

class Texture {
 private:
  SDL_Texture* texture;
  Surface surface;

 public:
  Texture(SDL_Renderer* renderer, const std::string& file);
  ~Texture();

  size_t get_width();
  size_t get_height();
  SDL_Texture* get_texture();
};

#endif
