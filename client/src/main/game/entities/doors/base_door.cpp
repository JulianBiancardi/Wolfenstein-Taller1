#include "base_door.h"

BaseDoor::BaseDoor(size_t x, size_t y, unsigned int resource_id)
    : x_pos(x), y_pos(y), resource_id(resource_id) {}

BaseDoor::~BaseDoor() {}

void BaseDoor::open() { state.open(); }

void BaseDoor::close() { state.close(); }

void BaseDoor::update() { state.update(); }

Image* BaseDoor::get_image(ResourceManager& resource_manager) {
  return resource_manager.get_image(resource_id);
}

SDL_Rect* BaseDoor::get_slice(void* extra) {
  state.set_slice(slice);
  return &slice;
}
