#include "drawable.h"

Drawable::Drawable() {
  slice.x = 0;
  slice.y = 0;
  slice.h = 64;
  slice.w = 64;
}

Drawable::~Drawable() {}

SDL_Rect* Drawable::get_slice(void* extra) {
  slice.x = 0;
  slice.y = 0;
  slice.h = 64;
  slice.w = 64;
  return &slice;
}