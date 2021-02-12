#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include "drawable.h"
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

  Image* get_image(ResourceManager& resource_manager);
};

#endif
