#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

#include "texture.h"

class Text {
 private:
  Texture texture;

 public:
  Text(SDL_Renderer* renderer, const std::string& text, TTF_Font* font,
       SDL_Color& color, SDL_Rect* pos);
  ~Text();
};

#endif  // TEXT_H