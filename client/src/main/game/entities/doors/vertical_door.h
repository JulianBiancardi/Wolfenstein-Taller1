#ifndef VERTICAL_DOOR_H
#define VERTICAL_DOOR_H

#include "base_door.h"

class VerticalDoor : public BaseDoor {
 private:
 public:
  VerticalDoor(size_t x, size_t y, unsigned int resource_id);
  ~VerticalDoor();

  Point get_collision_point(double x, double y, double angle) override;
  bool is_open_at(const Point& point) override;
};

#endif
