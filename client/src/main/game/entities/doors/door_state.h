#ifndef DOOR_STATE_H
#define DOOR_STATE_H

#include <SDL2/SDL.h>

#include <algorithm>

#include "../../../../../../common/src/main/config_loader.h"

enum door_state { closed, open };

class DoorState {
 private:
  double openness;
  double speed;

 public:
  DoorState(/* args */);
  ~DoorState();

  void open();
  void close();
  void update();
  void set_slice(SDL_Rect& slice);

  /* Receives a percentage of openness and returns true if the door is open by
   * at least that much, false otherwise. The percentage must be between 0
   * and 1. */
  bool is_open_by(double open_percentaje);
};

#endif
