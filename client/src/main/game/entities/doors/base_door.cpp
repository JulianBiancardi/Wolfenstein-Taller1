#include "base_door.h"

#include "../../../../../../common/src/main/ids/map_ids.h"

BaseDoor::BaseDoor(size_t x, size_t y, unsigned int resource_id)
    : x_pos(x), y_pos(y), resource_id(resource_id) {}

BaseDoor::~BaseDoor() {}

void BaseDoor::open() { state.open(); }

void BaseDoor::close() { state.close(); }

void BaseDoor::update() { state.update(); }

bool BaseDoor::requires_key() {
  resource_id == HORIZONTAL_DOOR || resource_id == VERTICAL_LOCKED_DOOR;
}

Image* BaseDoor::get_image(ResourceManager& resource_manager) {
  return resource_manager.get_image(resource_id);
}