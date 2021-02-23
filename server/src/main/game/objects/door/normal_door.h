#ifndef NORMAL_DOOR_H
#define NORMAL_DOOR_H

#include "door.h"

class NormalDoor : public Door {
 public:
  NormalDoor(const Point& center, unsigned int id);

  /* Returns if the door state changed */
  bool open(Player& who) override;
};

#endif
