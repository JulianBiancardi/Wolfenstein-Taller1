#ifndef CHEST_H
#define CHEST_H

#include "point_item.h"

class Chest : public PointItem {
 public:
  Chest(const Point& center, unsigned int id);

  /* Returns a copy of the element */
  Item* copy() override;

  /* Returns an add_item packet */
  virtual Packet get_add_item_packet() override;
};

#endif
