#include "locked_door.h"

#include "../../collisions/switch_mask.h"

LockedDoor::LockedDoor(const Point& center) : Door(center), locked(true) {}

bool LockedDoor::interact(Player& who, CollisionChecker& checker) {
  if (locked) {
    if (who.has_keys()) {
      locked = false;
      who.remove_key();
      ((SwitchMask*)mask)->switch_mask();
      return true;
    }
  } else {
    change_state(checker);
    return true;
  }

  return false;
}
