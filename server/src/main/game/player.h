#ifndef WOLFENSTEIN_TALLER1_PLAYER_H
#define WOLFENSTEIN_TALLER1_PLAYER_H

#include <iostream>
#include <vector>

#include "../../../../common/src/main/guns/gun.h"
#include "../config_loader.h"
#include "moveable.h"

class Player : public Moveable {
 private:
  int max_bullets;
  int bullets;
  int shot_bullets;
  int max_health;
  int health;
  int points;
  // std::map<std::string, Gun> guns_bag;
  // TODO Double check if pointers are needed
  std::vector<Gun*> guns_bag;
  Gun* active_gun;

 public:
  Player(Point origin, double angle, int id);
  Player(double x, double y, double angle, int id);
  ~Player() {}

  bool has_bullets(int amount);
  // void decrease_bullets(int amount);
  void receive_damage(int amount);
  void add_gun(Gun* gun);
  bool has_gun(Gun* gun);
  // bool add_gun_if_hasnt(Gun gun);
  void add_bullets(int amount);
  void add_points(int amount);
  void add_health(int amount);
  void decrease_health(int amount);
  bool is_full_health();
  int get_health();
};

#endif  // WOLFENSTEIN_TALLER1_PLAYER_H
