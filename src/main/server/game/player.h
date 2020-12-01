#ifndef WOLFENSTEIN_TALLER1_PLAYER_H
#define WOLFENSTEIN_TALLER1_PLAYER_H

#include "../../ray.h"
#include "map.h"

class Player {
 private:
  Ray angled_position;

 public:
  Player(Point origin, double angle) : angled_position(origin,angle) { };
  Player(int x, int y, double angle) : angled_position(x,y,angle) { };
  ~Player() { }

  void move_up();
  void move_down();
  void move_right();
  void move_left();
  void move_up_right();
  void move_up_left();
  void move_down_right();
  void move_down_left();

  Point get_position(){ return angled_position.get_origin(); };
};


#endif //WOLFENSTEIN_TALLER1_PLAYER_H
