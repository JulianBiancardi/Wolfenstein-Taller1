#ifndef WOLFENSTEIN_TALLER1_BLOOD_H
#define WOLFENSTEIN_TALLER1_BLOOD_H

#include "item.h"

class Blood : public Item {
 public:
  Blood(Point center, int id);
  void use(Player& user) override;
  Item* copy() override;
  bool can_be_used_by(Player& whom) override;
  void remove() override;

 private:
  int health_recovered;
  int less_than;
};

#endif  // WOLFENSTEIN_TALLER1_BLOOD_H
