#include "item.h"

#include "../../collisions/circle_mask.h"

Item::Item(Point center)
    : Object(center, 0,
             new CircleMask(CL::items_mask_radio,
                            this->position.get_ref_origin())) {}

Item::Item(Point center, int id)
    : Object(
          center, 0,
          new CircleMask(CL::items_mask_radio, this->position.get_ref_origin()),
          id) {}

Item::~Item() {}
