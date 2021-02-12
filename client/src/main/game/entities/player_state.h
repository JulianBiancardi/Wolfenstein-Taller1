#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include "updateable.h"

enum player_state { still, moving, dead };

class PlayerState : public Updateable {
 private:
  player_state current_state;
  player_state next_state;

 public:
  PlayerState();
  ~PlayerState();

  void update();
  void move();
  void kill();
  void print();
};

#endif
