#ifndef WOLFENSTEIN_TALLER1_MEDIC_KIT_H
#define WOLFENSTEIN_TALLER1_MEDIC_KIT_H

#include "items.h"

class MedicKit : public Items {
 public:
  MedicKit(Point center, int id);
  void use(Player &user) override;
  Items *copy() override;
  bool can_be_used_by(Player &whom) override;
  void remove() override;

 private:
  int health_recovered;
};

#endif //WOLFENSTEIN_TALLER1_MEDIC_KIT_H
