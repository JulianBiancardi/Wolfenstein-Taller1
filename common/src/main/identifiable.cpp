#include "identifiable.h"

Identifiable::Identifiable(unsigned int id) : id(id) {}

unsigned int Identifiable::get_id() const { return id; }
