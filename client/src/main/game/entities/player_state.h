#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include "updateable.h"

class PlayerState : public Updateable {
 private:
  bool moving;

 public:
  PlayerState();
  ~PlayerState();

  void update();
  void move();
};

#endif
