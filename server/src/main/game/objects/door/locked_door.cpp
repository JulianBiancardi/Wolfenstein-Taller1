#include "locked_door.h"

#include "../../collisions/switch_mask.h"

LockedDoor::LockedDoor(const Point& center, unsigned int id)
    : Door(center, id), locked(true) {}

bool LockedDoor::open(Player& who) {
  if (locked) {
    if (who.has_keys()) {
      locked = false;
      who.remove_key();
      change_state();
      return true;
    }
  } else {
    if (is_open()) {
      return false;
    } else {
      change_state();
      return true;
    }
  }
}
