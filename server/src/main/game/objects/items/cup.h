#ifndef CUP_H
#define CUP_H

#include "point_item.h"

class Cup : public PointItem {
 public:
  Cup(const Point& center, unsigned int id);

  /* Returns a copy of the element */
  Item* copy() override;

  /* Returns an add_item packet */
  virtual Packet get_add_item_packet() override;
};

#endif
