#include "object.h"

Object::Object(const Point& center, double angle, Mask* mask)
    : position(center, angle), mask(mask) {}

Object::Object(const Ray& position, Mask* mask)
    : position(position), mask(mask) {}

Object::Object(const Object& other)
    : position(other.position),
      mask(other.mask->get_copy(position.get_ref_origin())) {}

Object::~Object() { delete mask; }

bool Object::occupies(const Point& where) const {
  return mask->occupies(where);
}

Point Object::get_position() const { return position.get_origin(); }

double Object::get_angle() const { return position.get_angle(); }
