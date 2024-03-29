#include "item.h"

#include "../../collisions/circle_mask.h"

Item::Item(const Point& center, unsigned int id)
    : Object(center, 0,
             new CircleMask(CL::items_mask_radio,
                            this->position.get_ref_origin())),
      Identifiable(id) {}

Item::~Item() = default;
