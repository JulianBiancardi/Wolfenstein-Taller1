#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "../../../../common/src/main/utils/ray.h"
#include "collisions/circle_mask.h"

class Moveable {
 private:
  Ray angled_position;
/*  Map &map;
  int pace;*/
  Circle_mask mask;

/*  void move_from_current_position_if_can(double direction_angle);
  bool is_map_free_in_next_position(Point next_position);
  bool is_map_free_in_collision_mask_bounds(Point next_position,
                                            double movement_angle);*/

 public:
  Moveable(Point origin, double angle);
  Moveable(double x, double y, double angle);
  Moveable(const Moveable &other);
  ~Moveable() {}

  Point collision_mask_bound(const Point &next_position);
/*  void move_up();
  void move_down();
  void move_right();
  void move_left();
  void move_up_right();
  void move_up_left();
  void move_down_right();
  void move_down_left();*/
  bool occupies(Point where);
  bool operator!=(const Moveable &other) const;
  Point get_position() const { return angled_position.get_origin(); };
  Ray get_angled_position() const { return angled_position; };
  void set_position(const Point &new_origin);
};

#endif
