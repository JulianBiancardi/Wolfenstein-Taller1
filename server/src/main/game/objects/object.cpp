#include "object.h"

Object::Object(Point center, double angle, Mask* mask)
    : position(center, angle), mask(mask){};

Object::~Object() { delete mask; }

bool Object::occupies(Point where) { return mask->occupies(where); }
