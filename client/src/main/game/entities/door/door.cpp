#include "door.h"

Door::Door() {}

Door::~Door() {}

void Door::open() { state.open(); }

void Door::close() { state.close(); }

void Door::update() { state.update(); }

Image* Door::get_image(ResourceManager& resource_manager) {
  return resource_manager.get_image(resource_id);
}

SDL_Rect* Door::get_slice(void* extra) {
  state.set_slice(slice);
  return &slice;
}
