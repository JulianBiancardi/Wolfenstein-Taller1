#ifndef CROSS_H
#define CROSS_H

#include "point_item.h"

class Cross : public PointItem {
 public:
  Cross(const Point& center, unsigned int id);

  /* Returns a copy of the element */
  Item* copy() override;

  /* Returns an add_item packet */
  virtual Packet get_add_item_packet() override;
};

#endif
