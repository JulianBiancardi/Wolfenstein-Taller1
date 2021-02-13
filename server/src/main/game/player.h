#ifndef PLAYER_H
#define PLAYER_H

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
  // TODO Check how it copies
  const Point spawn_point;
  int lives;
  int players_killed;
  int keys;

  void remove_guns_to_respawn();

 public:
  Player(const Point& origin, double angle);
  Player(const Point& origin, double angle, unsigned int id);
  Player(double x, double y, double angle);
  Player(const Player& player);
  // TODO Define copy constructor so they can be put in storages. UPDATE:
  // DEFINED
  ~Player();

  /* Damages the player, health gets to 0 if killed */
  void receive_damage(int amount);

  /* Adds a gun */
  void add_gun(int gun_id);

  /* Returns if has gun */
  bool has_gun(int gun_id) const;

  /* Returns if has a gun that can be dropped when dead */
  bool has_droppable_gun();

  /* Change the active gun if it has it */
  bool change_gun(int gun_id);

  /* Shoots the gun, returns if had enough bullets to do it */
  bool shoot();

  /* Removes key if has */
  void remove_key();

  /* Returns if it is full health or not */
  bool is_full_health() const;

  /* Returns if it is full bullets or not */
  bool is_full_bullets() const;

  /* Returns if it is dead */
  bool is_dead() const;

  /* Returns if it has lives less */
  bool has_extra_lives() const;

  /* Returns if it has key */
  bool has_keys() const;

  /* Respawns the player */
  void respawn();

  /* Returns if the player is using a rocket launcher */
  bool is_using_rocket_launcher() const;

  /* Adders */
  void add_bullets(int amount);
  void add_points(int amount);
  void add_health(int amount);
  void add_key();
  void add_kill();

  /* Getters */
  int get_health() const;
  int get_bullets() const;
  int get_active_gun() const;
  int get_kills() const;
  int get_lives() const;
  int get_points() const;
};

#endif
