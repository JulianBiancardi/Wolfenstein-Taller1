#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include <SDL2/SDL.h>

enum player_state { stand, path, ghost };

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

  /* Enters ghost state, only a transparent image is drawn. */
  void become_ghost();

  /* Updates the slice */
  void set_slice(SDL_Rect& slice, double angle);

  /* Sets the state to moving. */
  void move();
};

#endif
