#ifndef WOLFENSTEIN_TALLER1_ITEMS_H
#define WOLFENSTEIN_TALLER1_ITEMS_H

#include "../sprite.h"
#include "../../player.h"

class Items : public Sprite {
 public:
  Items(Point center);
  ~Items();

  virtual void use(Player &user) = 0;
  virtual bool can_be_used_by(Player &whom) = 0;
  virtual void remove() = 0;
};

#endif //WOLFENSTEIN_TALLER1_ITEMS_H
