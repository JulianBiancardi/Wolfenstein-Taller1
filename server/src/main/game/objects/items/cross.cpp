#include "cross.h"

Cross::Cross(const Point& center, int id)
    : PointItem(center, CL::crosses_points, id) {}

Cross::Cross(const Point& center) : PointItem(center, CL::crosses_points) {}

Item* Cross::copy() { return new Cross(position.get_origin(), id); }
