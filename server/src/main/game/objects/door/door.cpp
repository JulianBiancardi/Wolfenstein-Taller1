#include "door.h"

#include "../../collisions/box_mask.h"
#include "../../collisions/switch_mask.h"

Door::Door(const Point& center)
    : Object(center, 0,
             new SwitchMask(new BoxMask(1, 1,
                                        this->position.get_ref_origin()))) {}

void Door::change_state(CollisionChecker& checker) {
  if (!is_open() || checker.is_free(position.get_ref_origin())) {
    ((SwitchMask*) mask)->switch_mask();
  }
}

bool Door::is_open() const { return !(((SwitchMask*) mask)->is_active()); }

void Door::close(CollisionChecker& checker) {
  if (is_open()) {
    change_state(checker);
  }
}
