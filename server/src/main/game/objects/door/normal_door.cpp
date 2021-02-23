#include "normal_door.h"

NormalDoor::NormalDoor(const Point& center, unsigned int id)
    : Door(center, id) {}

bool NormalDoor::open(Player& who) {
  if (is_open()) {
    return false;
  }

  change_state();
  return true;
}
