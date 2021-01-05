#ifndef WOLFENSTEIN_TALLER1_ROCKET_LAUNCHER_H
#define WOLFENSTEIN_TALLER1_ROCKET_LAUNCHER_H

#include "items.h"

class RocketLauncher : public Items {
 public:
  RocketLauncher(Point center, int id);
  void use(Player &user) override;
  Items *copy() override;
  bool can_be_used_by(Player &whom) override;
  void remove() override;

 private:
  static int health_recovered;
};

#endif //WOLFENSTEIN_TALLER1_ROCKET_LAUNCHER_H
