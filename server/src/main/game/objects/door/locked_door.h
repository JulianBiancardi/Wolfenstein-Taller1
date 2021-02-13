#ifndef LOCKED_DOOR_H
#define LOCKED_DOOR_H

#include "door.h"

class LockedDoor : public Door {
 private:
  bool locked;

 public:
  LockedDoor(const Point& center, unsigned int id);

  /* Returns if the door state changed */
  bool interact(Player& who, CollisionChecker& checker) override;
};

#endif
