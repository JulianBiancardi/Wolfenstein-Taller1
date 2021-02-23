#include "locked_door.h"

#include "../../collisions/switch_mask.h"

LockedDoor::LockedDoor(const Point& center, unsigned int id)
    : Door(center, id), locked(true) {}

bool LockedDoor::open(Player& who) {
  if (is_open()) {
    return false;
  }

  if (locked) {
    if (who.has_keys()) {
      locked = false;
      who.remove_key();
      change_state();
      return true;
    }
  } else {
    change_state();
    return true;
  }
}

bool LockedDoor::should_close_automatically() const {
  return true;
}
