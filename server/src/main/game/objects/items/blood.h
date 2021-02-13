#ifndef BLOOD_H
#define BLOOD_H

#include "item.h"

class Blood : public Item {
 private:
  int health_recovered;
  int less_than;

 public:
  Blood(const Point& center, unsigned int id);

  /* Item gets used by the player */
  void use(Player& user) override;

  /* Returns if the player can use the item */
  bool can_be_used_by(const Player& whom) override;

  /* Returns a copy of the element */
  Item* copy() override;

  /* Returns an add_item packet */
  virtual Packet get_add_item_packet() override;
};

#endif
