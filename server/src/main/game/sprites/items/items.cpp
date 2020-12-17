#include "items.h"

Items::Items(Point center, int id) : Sprite(center), Identifiable(id) {
  mask = new Circle_mask(0.5, this->center);
}

Items::~Items() {
  delete mask;
}

