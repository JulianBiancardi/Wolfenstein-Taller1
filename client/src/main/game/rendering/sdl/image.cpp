#include "image.h"

#include "sdl_error.h"

Image::Image(SDL_Renderer* renderer, const std::string& file)
    : renderer(renderer),
      texture(renderer, file),
      width(texture.get_width()),
      height(texture.get_height()) {}

Image::~Image() {}

void Image::draw(SDL_Rect* position, SDL_Rect* img_slice) {
  SDL_RenderCopy(renderer, texture.get_texture(), img_slice, position);
}

size_t Image::get_width() { return width; }
size_t Image::get_height() { return height; }
