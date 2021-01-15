#include "item.h"

#include "../../../../../../common/src/main/collisions/circle_mask.h"

Item::Item(Point center, int id)
    : Object(center, 0, new CircleMask(0.5, this->position.get_ref_origin())) {}

Item::~Item() {}
