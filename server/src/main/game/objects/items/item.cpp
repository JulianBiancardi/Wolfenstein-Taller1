#include "item.h"

Item::Item(Point center, int id)
    : Object(center, 0, new Circle_mask(0.5, center)), Identifiable(id) {}

Item::~Item() { delete mask; }
