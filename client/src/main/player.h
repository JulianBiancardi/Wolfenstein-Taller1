#ifndef WOLFENSTEIN_TALLER1_PLAYER_H
#define WOLFENSTEIN_TALLER1_PLAYER_H

#include <unordered_map>

#include "../../../common/src/main/collisions/circle_mask.h"
#include "../../../common/src/main/utils/point.h"
#include "../../../common/src/main/utils/ray.h"
#include "guns/gun.h"
#include "guns/hit.h"
#include "map.h"

class Gun;

class Player : public Object {
 private:
  Ray position;
  int pace;
  int health;
  int bullets;
  std::unordered_map<int, Gun*> guns_bag;
  int active_gun;

  Point next_position(double direction_angle);

 public:
  Player(Ray position);
  Player(Point origin, double angle);
  Player(double x, double y, double angle);
  ~Player();

  //
  void add_gun(int gun_num, Gun* gun);
  void set_gun(int gun_num);
  int get_health();
  void set_health(int health);
  bool has_bullets(int bullets);
  void decrease_bullets(int amount);
  //

  Point next_position_up();
  Point next_position_down();
  Point next_position_right();
  Point next_position_left();
  Point next_position_up_right();
  Point next_position_up_left();
  Point next_position_down_right();
  Point next_position_down_left();

  Ray get_position() { return position; };
  void set_position(const Point& new_origin);
  Hit shoot(Map& map);
};

#endif  // WOLFENSTEIN_TALLER1_PLAYER_H
