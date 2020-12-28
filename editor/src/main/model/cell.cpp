#include "include/cell.h"

#define BASE_ID 0

Cell::Cell() : id(BASE_ID) {}

size_t Cell::get_id() const { return this->id; }

void Cell::set_id(size_t value) {
  this->id = value;
  notify();
};

void Cell::clear() { set_id(BASE_ID); }

bool Cell::is_empty() const { return this->id == BASE_ID; };

Cell::~Cell() {}
