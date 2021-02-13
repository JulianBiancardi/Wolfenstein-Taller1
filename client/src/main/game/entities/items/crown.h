#ifndef CROWN_H
#define CROWN_H

#include "item.h"

class Crown : public Item {
 private:
 public:
  Crown(const Ray& position, unsigned int resource_id, unsigned int id);
  ~Crown();

  void use_on(Player& player);
};

#endif
