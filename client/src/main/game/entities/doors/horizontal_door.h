#ifndef HORIZONTAL_DOOR_H
#define HORIZONTAL_DOOR_H

#include "base_door.h"

class HorizontalDoor : public BaseDoor {
 private:
 public:
  HorizontalDoor(size_t x, size_t y, unsigned int resource_id);
  ~HorizontalDoor();

  Point get_collision_point(double x, double y, double angle) override;
  bool is_open_at(const Point& point) override;
};

#endif
