#ifndef WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_MOVEABLE_H_
#define WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_MOVEABLE_H_

#include "../../utils/ray.h"
#include "collisions/circle_mask.h"
#include "objects/object.h"

class Player;

class Moveable {
 private:
  Ray angled_position;
  Map &map;
  int pace;
  Circle_mask mask;

  void move_from_current_position_if_can(double direction_angle);
  bool is_map_free_in_next_position(Point next_position);
  bool is_map_free_in_collision_mask_bounds(Point next_position,
                                            double movement_angle);

 public:
  Moveable(Point origin, double angle, Map &game_map, int pace);
  ~Moveable() {}

  void move_up();
  void move_down();
  void move_right();
  void move_left();
  void move_up_right();
  void move_up_left();
  void move_down_right();
  void move_down_left();
  bool occupies(Point where);
  bool operator!=(const Moveable &other) const;
  Point get_position() { return angled_position.get_origin(); };
};

#endif  // WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_MOVEABLE_H_
