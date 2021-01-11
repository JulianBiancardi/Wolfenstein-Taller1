#include "item.h"

Item::Item(Point center, int id)
    : Object(center, 0, new Circle_mask(0.5, this->position.get_ref_origin())),
      Identifiable(id) {}

Item::~Item() {}
