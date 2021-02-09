#ifndef NORMAL_DOOR_H
#define NORMAL_DOOR_H

#include "door.h"

class NormalDoor : public Door {
 public:
  explicit NormalDoor(const Point& center);

  /* Returns if the door state changed */
  bool interact(Player& who, CollisionChecker& checker) override;
};

#endif
