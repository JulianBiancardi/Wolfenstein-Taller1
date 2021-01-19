#ifndef MEDIC_KIT_H
#define MEDIC_KIT_H

#include "item.h"

class MedicKit : public Item {
 public:
  MedicKit(Point center);
  void use(Player& user) override;
  Item* copy() override;
  bool can_be_used_by(Player& whom) override;

 private:
  MedicKit(Point center, int id);
  int health_recovered;
};

#endif
