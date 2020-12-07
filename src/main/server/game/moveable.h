#ifndef WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_MOVEABLE_H_
#define WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_MOVEABLE_H_

#include "../../ray.h"
#include "collisions/circle_mask.h"

class Map;

class Moveable {
 private:
  Ray angled_position;
  Map &map;
  int pace;
  Circle_mask mask;
  void move_from_current_position_if_can(double direction_angle);

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
  bool collides_wall(size_t x, size_t y, double movement_angle);
  Point get_position() { return angled_position.get_origin(); };
};

#endif //WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_MOVEABLE_H_
