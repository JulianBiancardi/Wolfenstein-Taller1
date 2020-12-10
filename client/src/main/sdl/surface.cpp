#include "surface.h"

#include "sdl_error.h"

Surface::Surface(std::string& file) {
  surface = SDL_LoadBMP(file.c_str());
  if (surface == NULL) {
    throw SDLError("SDLError: failed to load image '%s' - %s\n", file.c_str(),
                   SDL_GetError());
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