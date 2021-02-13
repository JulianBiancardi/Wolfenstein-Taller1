#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "../../../../../common/src/main/utils/point.h"
#include "../../../../../common/src/main/utils/ray.h"
#include "object.h"

class Moveable : public Object, public Identifiable {
 private:
  double speed;
  double rotation_speed;

  Point next_position(double direction_angle);

 public:
  Moveable(double x, double y, double angle, double speed,
           double rotation_speed, double radius, unsigned int id);
  Moveable(const Point& origin, double angle, double speed,
           double rotation_speed, double radius, unsigned int id);
  Moveable(const Ray& position, double speed, double rotation_speed,
           double radius, unsigned int id);

  Moveable(const Moveable& other);
  ~Moveable();

  /* Returns the next position given a direction */
  Point next_position(int direction);

  /* Rotates the moveable in the given direction */
  void rotate(int direction);

  /* Returns the point in bound of the mask in the direction of the position sent  */
  Point collision_mask_bound(const Point& next_position);

  /* Sets moveable position */
  void set_position(const Point& new_origin);
};

#endif
