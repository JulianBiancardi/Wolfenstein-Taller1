#include "include/cell.h"

#define BASE_ID 0
#define BASE_TYPE 0

Cell::Cell() : id(BASE_ID), type(BASE_TYPE) {}

size_t Cell::get_id() const { return this->id; }
size_t Cell::get_type() const { return this->type; }
void Cell::set_data(size_t id, size_t type) {
  this->id = id;
  this->type = type;
  notify();
};

void Cell::clear() { set_data(BASE_ID, BASE_TYPE); }

bool Cell::is_empty() const { return this->id == BASE_ID; };

Cell::~Cell() {}
