#ifndef WOLFENSTEIN_TALLER1_CHAIN_CANNON_H
#define WOLFENSTEIN_TALLER1_CHAIN_CANNON_H

#include "items.h"

class ChainCannon : public Items {
 public:
  ChainCannon(Point center);
  void use(Player &user) override;
  bool can_be_used_by(Player &whom) override;
  void remove() override;

 private:
  static int health_recovered;
};

#endif //WOLFENSTEIN_TALLER1_CHAIN_CANNON_H
