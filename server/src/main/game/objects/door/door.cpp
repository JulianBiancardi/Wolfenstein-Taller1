#include "door.h"

#include "../../collisions/box_mask.h"
#include "../../collisions/switch_mask.h"

Door::Door(const Point& center, unsigned int id)
    : Object(
          center, 0,
          new SwitchMask(new BoxMask(1, 1, this->position.get_ref_origin()))),
      Identifiable(id) {}

void Door::change_state() { ((SwitchMask*)mask)->switch_mask(); }

bool Door::is_open() const { return !(((SwitchMask*)mask)->is_active()); }

void Door::close() {
  if (is_open()) {
    change_state();
  }
}
