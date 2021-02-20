#include "door_state.h"

DoorState::DoorState() : openness(0), speed(0.0) {}

DoorState::~DoorState() {}

void DoorState::open() { speed = CL::door_speed / CL::fps; }

void DoorState::close() { speed = -CL::door_speed / CL::fps; }

void DoorState::update() {
  openness = std::max(0.0, std::max(64.0, openness += speed));
}

void DoorState::set_slice(SDL_Rect& slice) {
  slice.x = (int)openness;
  slice.y = 0;
  slice.h = 64;
  slice.w = 64;
}
