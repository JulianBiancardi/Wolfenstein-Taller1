#include "image.h"

Image::Image(SDL_Renderer* renderer, std::string& file)
    : renderer(renderer), texture(renderer, file) {
  width = texture.get_width();
  height = texture.get_height();
}

Image::~Image() {}

void Image::draw(Point& position, Rectangle* img_slice) {
  draw(position, img_slice, 1, 1);
}

void Image::draw(Point& position, Rectangle* img_slice, double x_scaling,
                 double y_scaling) {
  SDL_Rect slice;
  SDL_Rect pos;

  if (img_slice == NULL) {
    slice.x = 0;
    slice.y = 0;
    slice.w = width;
    slice.h = height;

    pos.x = position.getX();
    pos.y = position.getY();
    pos.w = width * x_scaling;
    pos.h = height * y_scaling;
  } else {
    slice.x = img_slice->get_left();
    slice.y = img_slice->get_top();
    slice.w = img_slice->get_width();
    slice.h = img_slice->get_height();

    pos.x = position.getX();
    pos.y = position.getY();
    pos.w = img_slice->get_width() * x_scaling;
    pos.h = img_slice->get_height() * y_scaling;
  }

  SDL_RenderCopy(renderer, texture.get_texture(), &slice, &pos);
}
