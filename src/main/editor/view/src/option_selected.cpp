#include "option_selected.h"

#define BASE_ID 0

OptionSelected::OptionSelected() { this->current_id = 3; }

size_t OptionSelected::get_current_id() const { return current_id; }

void OptionSelected::set_current_id(size_t value) { current_id = value; }

OptionSelected::~OptionSelected() {}