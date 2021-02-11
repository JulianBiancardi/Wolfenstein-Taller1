#ifndef MACHINE_GUN_ITEM_H
#define MACHINE_GUN_ITEM_H

#include "item.h"

class MachineGunItem : public Item {
 private:
  MachineGunItem(const Point& center, int id);

 public:
  explicit MachineGunItem(const Point& center);

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
