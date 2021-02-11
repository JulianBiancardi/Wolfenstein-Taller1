#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

#include "../../../../common/src/main/utils/rectangle.h"
#include "texture.h"

class Text {
 private:
  SDL_Renderer* renderer;
  Texture texture;
  size_t x_pos;
  size_t y_pos;

 public:
  Text(SDL_Renderer* renderer, const std::string& text, TTF_Font* font,
       SDL_Color& color, size_t x, size_t y);
  ~Text();
};

#endif  // TEXT_H