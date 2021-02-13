#include "normal_door.h"

NormalDoor::NormalDoor(const Point& center, unsigned int id)
    : Door(center, id) {}

bool NormalDoor::interact(Player& who, CollisionChecker& checker) {
  change_state(checker);
  return true;
}
