#include "cup.h"

Cup::Cup(const Point& center, int id) : PointItem(center, CL::cup_points, id) {}

Cup::Cup(const Point& center) : PointItem(center, CL::cup_points) {}

Item* Cup::copy() { return new Cup(position.get_origin(), id); }
