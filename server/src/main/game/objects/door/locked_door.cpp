#include "locked_door.h"

#include "../../collisions/switch_mask.h"

LockedDoor::LockedDoor(const Point& center, unsigned int id)
    : Door(center, id), locked(true) {}

bool LockedDoor::interact(Player& who, CollisionChecker& checker) {
  if (locked) {
    if (who.has_keys()) {
      locked = false;
      who.remove_key();
      change_state(checker);
      return true;
    }
  } else {
    change_state(checker);
    return true;
  }

  return false;
}
