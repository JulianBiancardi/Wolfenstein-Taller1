#include "texture.h"

Texture::Texture(SDL_Renderer* renderer, std::string& file) : surface(file) {
  texture = SDL_CreateTextureFromSurface(renderer, surface.get_surface());
}

Texture::~Texture() {
  if (texture != NULL) {
    SDL_DestroyTexture(texture);
  }
}

size_t Texture::get_width() { return surface.get_width(); }

size_t Texture::get_height() { return surface.get_height(); }

SDL_Texture* Texture::get_texture() { return texture; }
