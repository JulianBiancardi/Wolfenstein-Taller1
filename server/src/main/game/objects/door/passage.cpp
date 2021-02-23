#include "passage.h"

Passage::Passage(const Point& center, unsigned int id)
    : Door(center, id) {}

bool Passage::open(Player& who) {
  if (is_open()) {
    return false;
  } else {
    change_state();
    return true;
  }
}

bool Passage::should_close_automatically() const {
  return false;
}
