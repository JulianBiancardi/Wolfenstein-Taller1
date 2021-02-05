#include "door.h"
#include "../../../../../../common/src/main/collisions/switch_mask.h"
#include "../../../../../../common/src/main/collisions/box_mask.h"

Door::Door(const Point& center)
    : Object(center,
             0,
             new SwitchMask(new BoxMask(1,
                                        1,
                                        this->position.get_ref_origin()))) {}

void Door::change_state(CollisionChecker& checker) {
  if (!((SwitchMask*) mask)->is_active()
      && !checker.is_free(position.get_ref_origin()))
    return;

  ((SwitchMask*) mask)->switch_mask();
}

bool Door::is_open() const { return !(((SwitchMask*) mask)->is_active()); }

void Door::close(CollisionChecker& checker) {
  if (is_open()) {
    change_state(checker);
  }
}
