#include "crown.h"

Crown::Crown(const Point& center, int id)
    : PointItem(center, CL::crown_points, id) {}

Crown::Crown(const Point& center) : PointItem(center, CL::crown_points) {}

Item* Crown::copy() { return new Crown(position.get_origin(), id); }
