#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "../../../../common/src/main/object.h"
#include "../../../../common/src/main/utils/point.h"
#include "../../../../common/src/main/utils/ray.h"

class Moveable : public Object {
 private:
  double speed;
  double rotation_speed;

  Point next_position(double direction_angle);

 public:
  Moveable(Point origin, double angle, double speed, double rotation_speed,
           double radius);
  Moveable(Ray position, double speed, double rotation_speed, double radius);
  Moveable(double x, double y, double angle, double speed,
           double rotation_speed, double radius);
  Moveable(const Moveable& other);
  // TODO Add constructor with ID and also to player
  ~Moveable();

  Point next_position(int direction);
  void rotate(int direction);
  Point collision_mask_bound(const Point& next_position);
  bool operator!=(const Moveable& other) const;
  void set_position(const Point& new_origin);
};

#endif
