#ifndef WOLFENSTEIN_TALLER1_PLAYER_H
#define WOLFENSTEIN_TALLER1_PLAYER_H

#include <iostream>
#include <vector>

#include "../config_loader.h"
#include "guns/gun.h"
#include "moveable.h"
#include "shooter.h"

class Player : public Moveable {
 private:
  int max_bullets;
  int bullets;
  int shot_bullets;
  int max_health;
  int health;
  int points;
  // std::map<std::string, Gun> guns_bag;
  std::vector<Gun> guns_bag;
  Gun* active_gun;

 public:
  Player(Point origin, double angle, int id);
  Player(double x, double y, double angle, int id);
  ~Player() {}

  void shoot(Map& map);
  // void shoot_checker(double direction_angle);
  // void shoot_player(Player& shot_player, Gun& gun) override;
  bool has_bullets(int amount);
  // void decrease_bullets(int amount);
  void receive_damage(int amount);
  void add_gun(const Gun gun);
  bool has_gun(const Gun gun);
  // bool add_gun_if_hasnt(Gun gun);
  void add_bullets(int amount);
  void add_points(int amount);
  void add_health(int amount);
  void decrease_health(int amount);
  bool is_full_health();
  int get_health();
};

#endif  // WOLFENSTEIN_TALLER1_PLAYER_H
