#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "../../../../common/src/main/object.h"
#include "../../../../common/src/main/utils/point.h"
#include "../../../../common/src/main/utils/ray.h"

class Moveable : public Object {
 public:
  Moveable(Point origin, double angle);
  Moveable(Ray position);
  Moveable(double x, double y, double angle);
  Moveable(const Moveable& other);
  ~Moveable() {}

  Point collision_mask_bound(const Point& next_position);
  bool operator!=(const Moveable& other) const;
  void set_position(const Point& new_origin);
};

#endif
