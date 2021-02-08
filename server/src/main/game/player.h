#ifndef WOLFENSTEIN_TALLER1_PLAYER_H
#define WOLFENSTEIN_TALLER1_PLAYER_H

#include <iostream>
#include <unordered_set>

#include "../../../../common/src/main/config_loader.h"
#include "collisions/circle_mask.h"  //TODO Is needed?
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
  // TODO Check how it copies
  const Point spawn_point;
  int lives;
  int players_killed;
  int keys;
  Mask* knife_mask;

  void remove_guns_to_respawn();

 public:
  Player(Point origin, double angle);
  Player(double x, double y, double angle);
  Player(const Player& player);
  // TODO Define copy constructor so they can be put in storages. UPDATE:
  // DEFINED
  ~Player();

  // Player has too much responsibilities
  void receive_damage(int amount);
  void add_gun(int gun_id);
  bool has_gun(int gun_id) const;
  bool has_droppable_gun();
  bool change_gun(int gun_id);
  void shoot();
  void add_bullets(int amount);
  void add_points(int amount);
  void add_health(int amount);
  void add_key();
  void remove_key();
  bool is_full_health() const;
  bool is_full_bullets();
  bool is_dead() const;
  bool has_extra_lives();
  bool has_keys() const;
  void respawn();
  int get_health() const;
  int get_bullets() const;
  int get_active_gun() const;
  int get_kills();
  int get_lives();
  int get_points() const;
  void add_kill();
  Point knife_collision_mask_bound(const Point& next_position) const;
  bool knife_mask_bound_occupies(const Point& where) const;
};

#endif  // WOLFENSTEIN_TALLER1_PLAYER_H
