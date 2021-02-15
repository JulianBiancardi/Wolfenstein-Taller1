#include "text.h"

#include "sdl_error.h"

Text::Text(SDL_Renderer* renderer, const std::string& text, TTF_Font* font,
           SDL_Color& color, SDL_Rect* pos)
    : texture(renderer, text, font, color) {
  SDL_RenderCopy(renderer, texture.get_texture(), NULL, pos);
}

Text::~Text() {}
