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

  void draw(Point& position, Rectangle* img_slice);
  void draw(Point& position, Rectangle* img_slice, double x_scaling,
            double y_scaling);
  SDL_Texture* get_texture() { return texture.get_texture(); }
};

#endif