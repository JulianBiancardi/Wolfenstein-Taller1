#include "identifiable.h"

// TODO We might need to use this for object copying
Identifiable::Identifiable(int id) : id(id) {}

Identifiable::Identifiable() : id(next_id) { ++next_id; }

int Identifiable::next_id = 1;

void Identifiable::reset_id() { next_id = 1; }

int Identifiable::get_id() const { return id; }

void Identifiable::increase_id() { next_id++; }