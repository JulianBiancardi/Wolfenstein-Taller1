#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>

#include <string>

#include "../utils/point.h"
#include "../utils/rectangle.h"
#include "texture.h"

class Image {
 private:
  Texture texture;
  SDL_Renderer* renderer;
  size_t width;
  size_t height;

 public:
  Image(SDL_Renderer* renderer, std::string& file);
  ~Image();

  void draw(Rectangle& position, Rectangle* img_slice);
  size_t get_width();
  size_t get_height();
};

#endif