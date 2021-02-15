#include "player_state.h"

#include <iostream>

#include "../../../../../common/src/main/config_loader.h"
#include "../../../../../common/src/main/ids/gun_ids.h"
#include "../../../../../common/src/main/ids/map_ids.h"

#define RESET_AGE 1

PlayerState::PlayerState() : age(0), state(stand), moving(false) {}

PlayerState::~PlayerState() {}

void PlayerState::move() { moving = true; }

void PlayerState::update() {
  if (state == stand && moving == false) {
    return;
  } else if (state == path && moving == true) {
    age++;
    moving = false;
    return;
  } else if (state == stand && moving == true) {
    state = path;
    moving = false;
    return;
  } else if (state == path && moving == false) {
    if (age > RESET_AGE) {  // Allows to show extra frames of moving
      state = stand;
      age = 0;
      return;
    }
    age++;
    return;
  }
}

void PlayerState::set_slice(SDL_Rect& slice, double angle) {
  slice.x = ((int)((angle / (M_PI / 4)) + 4) % 8) * 64;
  slice.y = ((age / 2) % 4 + state) * 64;
  slice.w = 64;
  slice.h = 64;
}
