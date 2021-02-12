#include "player_state.h"

#include <iostream>

PlayerState::PlayerState() : current_state(still), next_state(still) {}

PlayerState::~PlayerState() {}

void PlayerState::update() {
  print();
  current_state = next_state;
  next_state = still;
}

void PlayerState::move() { next_state = moving; }

void PlayerState::kill() { next_state = dead; }

void PlayerState::print() {
  fprintf(stderr, "CS: %d\n", current_state);
  fprintf(stderr, "NS: %d\n", next_state);
}
