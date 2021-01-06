#ifndef MEDIC_KIT_H
#define MEDIC_KIT_H

#include "item.h"

class MedicKit : public Item {
 public:
  MedicKit(Point center, int id);
  void use(Player& user) override;
  Item* copy() override;
  bool can_be_used_by(Player& whom) override;
  void remove() override;

 private:
  int health_recovered;
};

#endif
