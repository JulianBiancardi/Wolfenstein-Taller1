#include "items.h"

Items::Items(Point center) : Sprite(center) {
  mask = new Circle_mask(0.5, this->center);
}

Items::~Items() {
  delete mask;
}

