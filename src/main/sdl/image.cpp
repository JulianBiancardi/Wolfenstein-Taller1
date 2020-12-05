#include "image.h"

Image::Image(SDL_Renderer* renderer, std::string file)
    : renderer(renderer), texture(renderer, file) {
  width = texture.get_width();
  height = texture.get_height();
}

Image::~Image() {}

void Image::draw(Point position, Rectangle img_slice) {
  SDL_Rect slice;
  slice.x = img_slice.get_left();
  slice.y = img_slice.get_top();
  slice.w = img_slice.get_width();
  slice.h = img_slice.get_height();

  SDL_Rect pos;
  pos.x = position.getX();
  pos.y = position.getY();
  pos.w = img_slice.get_width();
  pos.h = img_slice.get_height();

  SDL_RenderCopy(renderer, texture.get_texture(), &slice, &pos);
}
