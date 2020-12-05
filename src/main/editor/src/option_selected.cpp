#include "option_selected.h"

OptionSelected::OptionSelected() {
  this->current_id = -1;  // Invalid id
}

int OptionSelected::getCurrent_id() const { return current_id; }

void OptionSelected::setCurrent_id(int value) { current_id = value; }

OptionSelected::~OptionSelected() {}