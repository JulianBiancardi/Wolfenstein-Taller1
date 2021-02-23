#include "passage.h"

Passage::Passage(size_t x, size_t y, unsigned int resource_id)
    : BaseDoor(x, y, resource_id) {}

Passage::~Passage() {}

bool Passage::update_collision(Collision& collision, double angle) {
  return !state.is_open_by(0.0);
}

SDL_Rect* Passage::get_slice(void* extra) {
  slice.x = 0;
  slice.y = 64 - (int)(state.get_openness());
  slice.h = 64;
  slice.w = 64;
  return &slice;
}