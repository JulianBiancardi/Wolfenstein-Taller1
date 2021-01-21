#include "cross.h"

Cross::Cross(const Point& center) : PointItem(center, CL::crosses_points) {}

Cross::Cross(const Point& center, int id)
    : PointItem(center, CL::crosses_points, id) {}

Item* Cross::copy() { return new Cross(position.get_origin(), id); }
