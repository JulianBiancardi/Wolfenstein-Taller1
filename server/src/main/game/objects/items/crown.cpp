#include "crown.h"

Crown::Crown(const Point& center) : PointItem(center, CL::crown_points) {}

Crown::Crown(const Point& center, int id)
    : PointItem(center, CL::crown_points, id) {}

Item* Crown::copy() { return new Crown(position.get_origin(), id); }
