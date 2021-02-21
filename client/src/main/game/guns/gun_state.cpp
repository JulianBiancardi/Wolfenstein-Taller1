#include "gun_state.h"

GunState::GunState() {}

GunState::~GunState() {}

void GunState::update(bool shot) {
  if (!shot && state == ready) {
    return;
  } else if (state == shoot) {
    frame_count++;
    if (frame_count >= 3) {
      frame_count == 0;
      state = aim;
    }
  } else if (shot && state == ready) {
    state = aim;
    return;
  } else if (state == aim) {
    state = shoot;
    return;
  }
}

void GunState::set_slice(SDL_Rect& slice, double angle) {
  slice.x = 0;
  slice.y = 0;
  slice.w = 64;
  slice.h = 64;
}