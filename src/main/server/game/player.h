#ifndef WOLFENSTEIN_TALLER1_PLAYER_H
#define WOLFENSTEIN_TALLER1_PLAYER_H

#include "../config_loader.h"
#include <iostream>
#include "guns/gun.h"
#include <list>
#include "moveable.h"

class Player : public Moveable {
 private:
  int bullets;
  int shot_bullets;
  int health;
  int points;
  //std::map<std::string, Gun> guns_bag;
  std::list <Gun> guns_bag;

 public:
  Player(Point origin, double angle, Map &game_map);

  Player(double x, double y, double angle, Map &game_map);

  ~Player() {}

  void shoot_checker(double direction_angle);

  void shoot(Player &shot_player, Gun &gun);

  bool has_bullets(int amount);
/*
  void decrease_bullets(int amount);
*/
  void receive_damage(int amount);

  bool add_gun_if_hasnt(Gun gun);

  void add_points(int amount);

  void add_health(int amount);

  bool add_health_if_hass_less(int amount, int less_than);

  int get_health();
};

#endif //WOLFENSTEIN_TALLER1_PLAYER_H
