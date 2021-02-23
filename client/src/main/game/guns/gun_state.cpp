#include "gun_state.h"

#define PIXEL 1

GunState::GunState() : state(ready), frame_count(0) {}

GunState::~GunState() {}

void GunState::update(bool shot) {
  if (!shot && state == ready) {
    return;
  } else if (shot && state == ready) {
    state = shoot;
  } else if (state == shoot) {
    frame_count++;
    if (frame_count >= 4) {
      frame_count = 0;
      state = ready;
    }
  }
}

void GunState::set_slice(SDL_Rect& slice) {
  slice.x = frame_count * (PIXEL + 64);
  slice.y = 0;
  slice.w = 64;
  slice.h = 64;
}