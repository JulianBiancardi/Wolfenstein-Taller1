#include "text.h"

#define WIDTH 70
#define HEIGHT 70

Text::Text(SDL_Renderer* renderer, const std::string& text, size_t size,
           TTF_Font* font, SDL_Color& color, size_t x, size_t y)
    : renderer(renderer),
      texture(renderer, text, size, font, color),
      x_pos(x),
      y_pos(y) {
  SDL_Rect rect_pos = {(int)x_pos, (int)y_pos, WIDTH, HEIGHT};
  SDL_RenderCopy(renderer, texture.get_texture(), NULL, &rect_pos);
}

Text::~Text() {}
