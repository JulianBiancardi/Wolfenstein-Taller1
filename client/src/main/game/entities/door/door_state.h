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
};

DoorState::DoorState() : openness(0), speed(0.0) {}

DoorState::~DoorState() {}

void DoorState::open() { speed = CL::door_speed / CL::fps; }

void DoorState::close() { speed = -CL::door_speed / CL::fps; }

void DoorState::update() {
  openness = std::max(0.0, std::max(64.0, openness += speed));
}

void DoorState::set_slice(SDL_Rect& slice) {
  slice.x = openness;
  slice.y = 0;
  slice.h = 64;
  slice.w = 64;
}

#endif
