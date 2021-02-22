#ifndef HORIZONTAL_DOOR2_H
#define HORIZONTAL_DOOR2_H

#include "base_door.h"

class HorizontalDoor2 : public BaseDoor {
 private:
 public:
  HorizontalDoor2(size_t x, size_t y, unsigned int resource_id);
  ~HorizontalDoor2();

  bool update_collision(Collision& collision, double angle) override;
};

#endif
