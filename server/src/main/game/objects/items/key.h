#ifndef WOLFENSTEIN_TALLER1_KEY_H
#define WOLFENSTEIN_TALLER1_KEY_H

#include "items.h"

class Key : public Items {
 public:
  Key(Point center, int id);
  void use(Player &user) override;
  Items *copy() override;
  bool can_be_used_by(Player &whom) override;
  void remove() override;

};

#endif //WOLFENSTEIN_TALLER1_KEY_H
