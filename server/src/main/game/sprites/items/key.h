#ifndef WOLFENSTEIN_TALLER1_KEY_H
#define WOLFENSTEIN_TALLER1_KEY_H

#include "items.h"

class Key : public Items {
 public:
  Key(Point center);
  void use(Player &user) override;
  bool can_be_used_by(Player &whom) override;
  void remove() override;

};

#endif //WOLFENSTEIN_TALLER1_KEY_H
