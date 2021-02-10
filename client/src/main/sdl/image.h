#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

#include "../../../../common/src/main/utils/rectangle.h"
#include "texture.h"

class Image {
 private:
  SDL_Renderer* renderer;
  Texture texture;
  int width;
  int height;

 public:
  Image(SDL_Renderer* renderer, const std::string& file);
  ~Image();

  void draw(Rectangle& position, Rectangle* img_slice);
  void draw(SDL_Rect* position, SDL_Rect* img_slice);

  size_t get_width();
  size_t get_height();
};

#endif