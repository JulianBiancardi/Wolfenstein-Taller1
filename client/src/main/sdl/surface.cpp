#include "surface.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "sdl_error.h"

Surface::Surface(const std::string& file) {
  surface = IMG_Load(file.c_str());
  if (surface == NULL) {
    throw SDLError("SDLError: failed to load image '%s' - %s\n", file.c_str(),
                   SDL_GetError());
  }
  if (surface->format != nullptr) {
    if (SDL_SetColorKey(surface, SDL_TRUE,
                        SDL_MapRGB(surface->format, 152, 00, 136))) {
      throw SDLError("SDLError: failed to set color key - %s\n",
                     SDL_GetError());
    }
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