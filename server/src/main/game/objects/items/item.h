#ifndef ITEMS_H
#define ITEMS_H

#include "../../../../../../common/src/main/packets/packet.h"
#include "../../../../../../common/src/main/packets/packing.h"
#include "../../player.h"
#include "../object.h"

class Item : public Object {
 protected:
  Item(const Point& center, int id);

 public:
  explicit Item(const Point& center);
  ~Item() override;

  /* Item gets used by the player */
  virtual void use(Player& user) = 0;

  /* Returns if the player can use the item */
  virtual bool can_be_used_by(const Player& whom) = 0;

  /* Returns a copy of the element */
  virtual Item* copy() = 0;  // Deep copying

  /* Returns an add_item packet */
  virtual Packet get_add_item_packet() = 0;
};

#endif
