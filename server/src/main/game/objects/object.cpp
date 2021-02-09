#include "object.h"

Object::Object(const Point& center, double angle, Mask* mask, int id)
    : position(center, angle), mask(mask), Identifiable(id) {}

Object::Object(const Point& center, double angle, Mask* mask)
    : position(center, angle), mask(mask), Identifiable() {}

Object::Object(const Ray& position, Mask* mask, int id)
    : position(position), mask(mask), Identifiable(id) {}

Object::Object(const Ray& position, Mask* mask)
    : position(position), mask(mask) {}

Object::~Object() { delete mask; }

bool Object::occupies(const Point& where) const {
  return mask->occupies(where);
}

Point Object::get_position() const { return position.get_origin(); }

double Object::get_angle() const { return position.get_angle(); }
