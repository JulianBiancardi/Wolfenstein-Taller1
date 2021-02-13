#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <SDL2/SDL.h>

#include "point.h"

class Rectangle {
 private:
  size_t left;
  size_t right;
  size_t top;
  size_t bot;

 public:
  Rectangle(size_t top, size_t left, size_t width, size_t height);
  ~Rectangle();
  size_t get_left();
  size_t get_right();
  size_t get_top();
  size_t get_bot();
  size_t get_width();
  size_t get_height();
};

#endif
