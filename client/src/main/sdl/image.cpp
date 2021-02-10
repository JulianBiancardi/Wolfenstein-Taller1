#include "image.h"

#include "sdl_error.h"

Image::Image(SDL_Renderer* renderer, const std::string& file)
    : renderer(renderer), texture(renderer, file) {
  SDL_QueryTexture(texture.get_texture(), nullptr, nullptr, &width, &height);
}

Image::~Image() {}

void Image::draw(Rectangle& position, Rectangle* img_slice) {
  SDL_Rect pos;
  pos.x = position.get_left();
  pos.y = position.get_top();
  pos.w = position.get_width();
  pos.h = position.get_height();

  SDL_Rect slice;
  if (img_slice == nullptr) {
    slice.x = 0;
    slice.y = 0;
    slice.w = width;
    slice.h = height;
  } else {
    slice.x = img_slice->get_left();
    slice.y = img_slice->get_top();
    slice.w = img_slice->get_width();
    slice.h = img_slice->get_height();
  }

  SDL_RenderCopy(renderer, texture.get_texture(), &slice, &pos);
}

void Image::draw(SDL_Rect* position, SDL_Rect* img_slice) {
  SDL_RenderCopy(renderer, texture.get_texture(), img_slice, position);
}

size_t Image::get_width() { return width; }
size_t Image::get_height() { return height; }
