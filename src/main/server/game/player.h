#ifndef WOLFENSTEIN_TALLER1_PLAYER_H
#define WOLFENSTEIN_TALLER1_PLAYER_H
#include "../config_loader.h"
#include "../../ray.h"
#include "map.h"

//#include "guns/chain_cannon.h"
#include <iostream>

//class Gun;
class Player {
 private:
  Ray angled_position;
  //
  int bullets;
  int shot_bullets;
  int health;
  int points;

  //Gun& gun;
  //std::list<Gun&> guns;
  //

 public:
    Player(Point origin, double angle);
    Player(int x, int y, double angle);
/*
  Player(Point origin, double angle) : angled_position(origin,angle) { };
  Player(int x, int y, double angle) : angled_position(x,y,angle) { };
*/
  ~Player() { }

  void move_from_current_position_if_can(int x, int y);
  void move_up();
  void move_down();
  void move_right();
  void move_left();
  void move_up_right();
  void move_up_left();
  void move_down_right();
  void move_down_left();
  //
  void shoot(Player& shot_player);
  bool has_bullets(int amount);
  void decrease_bullets(int amount);
  void receive_damage(int amount);
  bool add_gun_if_hasnt(/*Gun& gun*/);
  void add_points(int amount);
  void add_health(int amount);
  bool add_health_if_hass_less(int amount, int less_than);

  int get_health();
  //
  Point get_position(){ return angled_position.get_origin(); };
};


#endif //WOLFENSTEIN_TALLER1_PLAYER_H
