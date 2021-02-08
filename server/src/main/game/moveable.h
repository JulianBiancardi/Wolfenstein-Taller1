#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "../../../../common/src/main/utils/point.h"
#include "../../../../common/src/main/utils/ray.h"
#include "objects/object.h"

class Moveable : public Object {
 private:
  double pace;
  double rotation_angle;

  Point next_position(double direction_angle);

 public:
  Moveable(Point origin, double angle);
  Moveable(Ray position);
  Moveable(double x, double y, double angle);
  Moveable(const Moveable& other);
  // TODO Add constructor with ID and also to player
  ~Moveable() {}

  Point next_position(int direction);
  void rotate(int direction);
  Point collision_mask_bound(const Point& next_position);
  bool operator!=(const Moveable& other) const;
  void set_position(const Point& new_origin);
};

#endif
