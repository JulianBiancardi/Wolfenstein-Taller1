#include "door_state.h"

DoorState::DoorState() : openness(0.0), speed(0.0) {}

DoorState::~DoorState() {}

void DoorState::open() { speed = 64 * CL::door_speed / CL::fps; }

void DoorState::close() { speed = 64 * -CL::door_speed / CL::fps; }

void DoorState::update() {
  openness = std::max(0.0, std::min(64.0, openness += speed));
}

bool DoorState::is_open_by(double amount) {
  printf("%f > %f ?\n", amount, (1.0 - (openness) / 64.0));
  return amount >= (1.0 - (openness) / 64.0);
}

double DoorState::get_openness() { return openness; }
