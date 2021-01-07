#ifndef COLLISION_H
#define COLLISION_H

#include "../../../common/src/main/utils/point.h"

class Collision {
 private:
  int collided_obj_id;
  Point collision_point;
  double distance_from_src;
  bool x_collision;

 public:
  Collision(int id, Point point, double distance_from_src, bool x_collision);
  ~Collision();

  int get_collided_obj_id();
  Point get_collision_point();
  double get_distance_from_src();
  bool is_x_collision();
};

#endif
