#ifndef LOCKED_DOOR_H
#define LOCKED_DOOR_H

#include "door.h"

class LockedDoor : public Door {
 private:
  bool locked;

 public:
  LockedDoor(const Point& center, unsigned int id);

  bool open(Player& who) override;
};

#endif
