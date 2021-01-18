#include "object.h"

Object::Object(Point center, double angle, Mask* mask)
    : position(center, angle), mask(mask), Identifiable() {}

Object::Object(Point center, double angle, Mask* mask, int id)
    : position(center, angle), mask(mask), Identifiable(id) {}

Object::Object(Ray position, Mask* mask, int id)
    : position(position), mask(mask), Identifiable(id) {}

Object::Object(Ray position, Mask* mask) : position(position), mask(mask) {}

Object::~Object() { delete mask; }

Point Object::get_position() { return position.get_origin(); }
double Object::get_angle() { return position.get_angle(); }

bool Object::occupies(Point& where) { return mask->occupies(where); }
