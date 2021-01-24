#include "normal_door.h"
#include "../../../../../../common/src/main/collisions/switch_mask.h"

NormalDoor::NormalDoor(const Point& center) : Door(center) {}

void NormalDoor::interact(Player& who, CollisionChecker& checker) {
  change_state(checker);
}
