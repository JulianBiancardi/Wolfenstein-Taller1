#include "cup.h"

Cup::Cup(const Point& center) : PointItem(center, CL::cup_points) {}

Cup::Cup(const Point& center, int id) : PointItem(center, CL::cup_points, id) {}

Item* Cup::copy() { return new Cup(position.get_origin(), id); }
