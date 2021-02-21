#ifndef GUN_STATE_H
#define GUN_STATE_H

#include <SDL2/SDL.h>

enum gun_state { ready, aim, shoot };

class GunState {
 private:
  gun_state state;
  int frame_count;

 public:
  GunState();
  ~GunState();

  /* Updates the state. */
  void update(bool trigger);

  /* Updates the slice */
  void set_slice(SDL_Rect& slice, double angle);
};

#endif
