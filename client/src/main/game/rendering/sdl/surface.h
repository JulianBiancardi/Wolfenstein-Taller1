#ifndef SURFACE_H
#define SURFACE_H

#include <SDL2/SDL.h>

#include <string>

class Surface {
 private:
  SDL_Surface* surface;

 public:
  Surface(std::string& file);
  ~Surface();

  size_t get_width();
  size_t get_height();
  SDL_Surface* get_surface();
};

#endif
