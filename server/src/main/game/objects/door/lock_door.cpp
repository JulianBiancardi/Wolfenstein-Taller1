#include "lock_door.h"
#include "../../../../../../common/src/main/collisions/switch_mask.h"

LockedDoor::LockedDoor(const Point& center) : Door(center), locked(true) {}

void LockedDoor::interact(Player& who, CollisionChecker& checker) {
  if (locked) {
    if (who.has_keys()) {
      locked = false;
      who.remove_key();
      ((SwitchMask*) mask)->switch_mask();
    }
  } else {
    change_state(checker);
  }
}
