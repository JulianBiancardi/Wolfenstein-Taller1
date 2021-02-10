#include "text.h"

#define FONT_PATH                                                          \
  "/home/julian/JULIAN/Taller1/Wolfenstein-Taller1/client/src/main/fonts/" \
  "wolfenstein.ttf"
#define WIDTH 70
#define HEIGHT 70

Text::Text(SDL_Renderer* renderer, const std::string& text, size_t size,
           SDL_Color& color, size_t x, size_t y)
    : renderer(renderer), color(color), x_pos(x), y_pos(y) {
  font = TTF_OpenFont(FONT_PATH, size);

  surface = TTF_RenderText_Solid(font, text.c_str(), color);
  texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_Rect rect_pos = {(int)x_pos, (int)y_pos, WIDTH, HEIGHT};
  SDL_RenderCopy(renderer, texture, NULL, &rect_pos);
}

Text::~Text() {
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}
