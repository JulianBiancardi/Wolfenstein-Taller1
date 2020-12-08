#include "object.h"

bool Object::occupies(Point where) {
  return mask->occupies(where);
}
