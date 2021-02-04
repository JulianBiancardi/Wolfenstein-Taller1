#ifndef PLAYER_H
#define PLAYER_H

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

 public:
  Player(Ray position);
  Player(Point origin, double angle);
  Player(double x, double y, double angle);
  ~Player();

  void move(unsigned char direction);
  void rotate(unsigned char direction);

  //
  void add_gun(int gun_num, Gun* gun);
  void set_gun(int gun_num);
  int get_health();
  void set_health(int health);
  bool has_bullets(int bullets);
  void decrease_bullets(int amount);

  Hit shoot(Map& map);
};

#endif
