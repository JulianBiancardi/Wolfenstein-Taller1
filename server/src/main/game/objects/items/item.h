#ifndef ITEMS_H
#define ITEMS_H

#include "../../../../../../common/src/main/packets/packet.h"
#include "../../../../../../common/src/main/packets/packing.h"
#include "../player.h"
#include "../object.h"

class Item : public Object, public Identifiable {
 protected:
  Item(const Point& center, unsigned int id);

 public:
  ~Item() override;

  /* Item gets used by the player */
  virtual void use(Player& user) = 0;

  /* Returns if the player can use the item */
  virtual bool can_be_used_by(const Player& whom) = 0;
};

#endif
