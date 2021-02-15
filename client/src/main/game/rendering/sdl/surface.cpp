#include "surface.h"

#include "sdl_error.h"

Surface::Surface(const std::string& file) {
  surface = IMG_Load(file.c_str());
  if (surface == nullptr) {
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

Surface::Surface(const std::string& text, TTF_Font* font, SDL_Color& color) {
  if (font == nullptr) {
    throw SDLError("SDLError: failed to load font - %s\n", SDL_GetError());
  }
  surface = TTF_RenderText_Solid(font, text.c_str(), color);
  if (surface == nullptr) {
    throw SDLError("SDLError: failed to load text - %s\n", SDL_GetError());
  }
}

Surface::~Surface() {
  if (surface != NULL) {
    SDL_FreeSurface(surface);
  }
}

size_t Surface::get_width() const { return surface->w; }

size_t Surface::get_height() const { return surface->h; }

SDL_Surface* Surface::get_surface() const { return surface; }