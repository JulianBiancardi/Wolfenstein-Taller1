#include "chest.h"

Chest::Chest(const Point& center) : PointItem(center, CL::chests_points) {}

Chest::Chest(const Point& center, int id)
    : PointItem(center, CL::chests_points, id) {}

Item* Chest::copy() { return new Chest(position.get_origin(), id); }
