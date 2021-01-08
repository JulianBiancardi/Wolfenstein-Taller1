#ifndef WOLFENSTEIN_TALLER1_PLAYER_H
#define WOLFENSTEIN_TALLER1_PLAYER_H

#include "../../../common/src/main/utils/ray.h"
#include "map.h"

class Player {
 private:
  Ray position;
  int pace;

  //
  int health;
  //

  Point next_position(double direction_angle);

 public:
  Player(Point origin, double angle);
  Player(double x, double y, double angle);
  ~Player() {}

  //
  void set_health(int health);
  //

  Point next_position_up();
  Point next_position_down();
  Point next_position_right();
  Point next_position_left();
  Point next_position_up_right();
  Point next_position_up_left();
  Point next_position_down_right();
  Point next_position_down_left();

  Point get_position() { return position.get_origin(); };
  void set_position(const Point& new_origin);
  void Player::shoot(Map& map);
};

#endif  // WOLFENSTEIN_TALLER1_PLAYER_H
