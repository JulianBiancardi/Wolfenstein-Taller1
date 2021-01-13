#ifndef WOLFENSTEIN_TALLER1_PLAYER_H
#define WOLFENSTEIN_TALLER1_PLAYER_H

#include <iostream>
#include <unordered_set>

#include "../../../../common/src/main/config_loader.h"
#include "moveable.h"
class Gun;
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
  std::unordered_set<int> guns_bag;
  int active_gun;

 public:
  Player(Point origin, double angle, int id);
  Player(double x, double y, double angle, int id);
  ~Player();

  // bool has_bullets(int amount);
  // void decrease_bullets(int amount); //why not?
  void receive_damage(int amount);
  void add_gun(int gun_id);
  bool has_gun(int gun_id);
  void shoot(Player& enemy_shot, double damage_done, int bullets_shot);
  // bool add_gun_if_hasnt(Gun gun);
  void add_bullets(int amount);
  void add_points(int amount);
  void add_health(int amount);
  void decrease_health(int amount);
  void decrease_bullets_2(int amount);
  bool is_full_health();
  int get_current_health();
  int get_current_bullets();
};

#endif  // WOLFENSTEIN_TALLER1_PLAYER_H
