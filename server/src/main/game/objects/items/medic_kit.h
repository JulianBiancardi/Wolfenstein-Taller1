#ifndef MEDIC_KIT_H
#define MEDIC_KIT_H

#include "item.h"

class MedicKit : public Item {
 private:
  int health_recovered;

 public:
  MedicKit(const Point& center, unsigned int id);

  /* Item gets used by the player */
  void use(Player& user) override;

  /* Returns if the player can use the item */
  bool can_be_used_by(const Player& whom) override;
};

#endif
