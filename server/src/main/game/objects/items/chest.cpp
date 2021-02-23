#include "chest.h"

Chest::Chest(const Point& center, unsigned int id)
    : PointItem(center, id, CL::chest_points) {}
