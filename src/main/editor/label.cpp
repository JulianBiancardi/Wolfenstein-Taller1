#include "label.h"

Label::Label(SDL_Renderer* renderer, const std::string& text, TTF_Font* font,
             SDL_Color color) {
  // Generate the surface
  SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

  if (surface == NULL) {
    throw -1;  // TODO
  }
  // Create the texture
  this->texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_FreeSurface(surface);
}

Label::~Label() { SDL_DestroyTexture(this->texture); }
