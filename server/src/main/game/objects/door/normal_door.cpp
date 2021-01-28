#include "normal_door.h"

NormalDoor::NormalDoor(const Point& center) : Door(center) {}

bool NormalDoor::interact(Player& who, CollisionChecker& checker) {
  change_state(checker);
  return true;
}
