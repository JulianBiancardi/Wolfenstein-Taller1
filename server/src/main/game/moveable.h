#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "../../../../common/src/main/utils/ray.h"
#include "collisions/circle_mask.h"
#include "identifiable.h"
#include "objects/object.h"

class Moveable : public Object, public Identifiable {
 private:
  /*  Map &map;
    int pace;*/

  /*  void move_from_current_position_if_can(double direction_angle);
    bool is_map_free_in_next_position(Point next_position);
    bool is_map_free_in_collision_mask_bounds(Point next_position,
                                              double movement_angle);*/

 public:
  Moveable(Point origin, double angle, int id);
  Moveable(Ray position, int id);
  Moveable(double x, double y, double angle, int id);
  Moveable(const Moveable &other) = delete;
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
  bool operator!=(const Moveable &other) const;
  void set_position(const Point &new_origin);
};

#endif
