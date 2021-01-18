#ifndef WOLFENSTEIN_TALLER1_PLAYER_H
#define WOLFENSTEIN_TALLER1_PLAYER_H

#include <iostream>
#include <unordered_set>

#include "../../../../common/src/main/config_loader.h"
#include "moveable.h"

class Player : public Moveable {
 private:
  int max_bullets;
  int bullets;
  int shot_bullets;
  int max_health;
  int health;
  int points;
  std::unordered_set<int> guns_bag;
  int active_gun;
  const Point spawn_point;
  int lives;

 public:
  Player(Point origin, double angle, int id);
  Player(double x, double y, double angle, int id);
  ~Player() {}

  void receive_damage(int amount);
  void add_gun(int gun_id);
  bool has_gun(int gun_id);
  void change_gun(int gun_id);
  void shoot(Player& enemy_shot, double damage_done, int bullets_shot);
  void add_bullets(int amount);
  void add_points(int amount);
  void add_health(int amount);
  void decrease_bullets(int amount);
  bool is_full_health();
  bool is_full_bullets();
  bool is_dead();
  bool has_lives_left();
  void respawn();
  int get_health();
  int get_bullets();
  int get_active_gun();
};

#endif  // WOLFENSTEIN_TALLER1_PLAYER_H
