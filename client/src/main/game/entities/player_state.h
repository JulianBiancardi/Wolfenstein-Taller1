#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include <SDL2/SDL.h>

enum player_state { stand, path };

class PlayerState {
 private:
  long age;
  player_state state;
  bool moving;

 public:
  PlayerState();
  explicit PlayerState(long age, player_state state, bool moving);
  ~PlayerState();

  /* Updates the state. */
  void update();

  /* Updates the slice */
  void set_slice(SDL_Rect& slice, double angle);

  /* Sets the state to moving. */
  void move();
};

#endif
