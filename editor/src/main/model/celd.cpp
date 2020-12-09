#include "celd.h"

#define BASE_ID 0

Celd::Celd() : id(BASE_ID) {}

size_t Celd::get_id() const { return this->id; }

void Celd::set_id(size_t value) {
  this->id = value;
  notify();
};

void Celd::clear() {
  this->id = BASE_ID;
  notify();
}

bool Celd::is_empty() const { return this->id == BASE_ID; };

Celd::~Celd() {}
