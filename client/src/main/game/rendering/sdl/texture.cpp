#include "texture.h"

#include "sdl_error.h"

Texture::Texture(SDL_Renderer* renderer, const std::string& image)
    : surface(image) {
  texture = SDL_CreateTextureFromSurface(renderer, surface.get_surface());
  if (texture == NULL) {
    throw SDLError("SDLError: failed to create texture - %s\n", SDL_GetError());
  }
}

Texture::Texture(SDL_Renderer* renderer, const std::string& text,
                 TTF_Font* font, SDL_Color& color)
    : surface(text, font, color) {
  texture = SDL_CreateTextureFromSurface(renderer, surface.get_surface());
  if (texture == NULL) {
    throw SDLError("SDLError: failed to create texture - %s\n", SDL_GetError());
  }
}

Texture::~Texture() {
  if (texture != NULL) {
    SDL_DestroyTexture(texture);
  }
}

size_t Texture::get_width() const { return surface.get_width(); }

size_t Texture::get_height() const { return surface.get_height(); }

SDL_Texture* Texture::get_texture() const { return texture; }
