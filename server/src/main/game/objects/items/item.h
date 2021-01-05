#ifndef ITEMS_H
#define ITEMS_H

#include "../../player.h"
#include "../object.h"

class Items : public Object, public Identifiable {
 public:
  Items(Point center, int id);
  ~Items();

  virtual void use(Player& user) = 0;
  virtual bool can_be_used_by(Player& whom) = 0;
  virtual Items* copy() = 0;  // Deep copying
  virtual void remove() = 0;
};

#endif  // WOLFENSTEIN_TALLER1_ITEMS_H
