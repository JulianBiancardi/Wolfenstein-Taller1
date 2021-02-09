#ifndef LOCKED_DOOR_H
#define LOCKED_DOOR_H

#include "door.h"

class LockedDoor : public Door {
 private:
  bool locked;

 public:
  explicit LockedDoor(const Point& center);

  /* Returns if the door state changed */
  bool interact(Player& who, CollisionChecker& checker) override;
};

#endif
