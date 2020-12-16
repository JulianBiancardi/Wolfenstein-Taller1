#ifndef WOLFENSTEIN_TALLER1_BULLETS_H
#define WOLFENSTEIN_TALLER1_BULLETS_H

#include "items.h"

class Bullets : public Items {
 public:
  Bullets(Point center);
  void use(Player &user) override;
  bool can_be_used_by(Player &whom) override;
  void remove() override;

 private:
  int amount;
};

#endif //WOLFENSTEIN_TALLER1_BULLETS_H
