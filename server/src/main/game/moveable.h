#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "../../../../common/src/main/utils/ray.h"
#include "collisions/circle_mask.h"
#include "identifiable.h"
#include "../../../../common/src/main/object.h"

class Moveable : public Object, public Identifiable {
 public:
  Moveable(Point origin, double angle, int id);
  Moveable(Ray position, int id);
  Moveable(double x, double y, double angle, int id);
  Moveable(const Moveable& other);
  ~Moveable() {}

  Point collision_mask_bound(const Point& next_position);
  bool operator!=(const Moveable& other) const;
  void set_position(const Point& new_origin);
};

#endif
