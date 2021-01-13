#ifndef ITEMS_H
#define ITEMS_H

#include "../../player.h"
#include "../../../../../../common/src/main/object.h"

class Item : public Object, public Identifiable {
 public:
  Item(Point center, int id);
  ~Item();

  virtual void use(Player& user) = 0;
  virtual bool can_be_used_by(Player& whom) = 0;
  virtual Item* copy() = 0;  // Deep copying
  virtual void remove() = 0;
};

#endif  // WOLFENSTEIN_TALLER1_ITEMS_H
