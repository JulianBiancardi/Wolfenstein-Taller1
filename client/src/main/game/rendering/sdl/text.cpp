#include "text.h"

#include "sdl_error.h"

Text::Text(SDL_Renderer* renderer, const std::string& text, TTF_Font* font,
           SDL_Color& color)
    : renderer(renderer), texture(renderer, text, font, color) {}

void Text::draw(int x_pos, int y_pos) {
  position.x = x_pos;
  position.y = y_pos;
  SDL_QueryTexture(texture.get_texture(), nullptr, nullptr, &(position.w),
                   &(position.h));
  SDL_RenderCopy(renderer, texture.get_texture(), nullptr, &position);
}

Text::~Text() {}
