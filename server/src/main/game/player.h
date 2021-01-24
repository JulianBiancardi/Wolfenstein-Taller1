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
  int players_killed;
  int keys;

  void remove_guns_to_respawn();

 public:
  Player(Point origin, double angle);
  Player(double x, double y, double angle);
  ~Player();

  // Player has too much responsibilities
  void receive_damage(int amount);
  void add_gun(int gun_id);
  bool has_gun(int gun_id);
  bool has_droppable_gun();
  bool change_gun(int gun_id);
  void shoot();
  void add_bullets(int amount);
  void add_points(int amount);
  void add_health(int amount);
  void add_key();
  void remove_key();
  bool is_full_health();
  bool is_full_bullets();
  bool is_dead();
  bool has_lives();
  bool has_keys();
  void respawn();
  int get_health();
  int get_bullets();
  int get_active_gun();
  int get_kills();
  int get_lives();
  int get_points();
  void add_kill();
};

#endif  // WOLFENSTEIN_TALLER1_PLAYER_H
