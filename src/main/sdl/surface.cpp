#include "surface.h"

Surface::Surface(std::string& file) {
  surface = SDL_LoadBMP(file.c_str());
  if (surface == NULL) {
    throw 1;  // TODO Change to error
  }
}

Surface::~Surface() {
  if (surface != NULL) {
    SDL_FreeSurface(surface);
  }
}

size_t Surface::get_width() { return surface->w; }

size_t Surface::get_height() { return surface->h; }

SDL_Surface* Surface::get_surface() { return surface; }