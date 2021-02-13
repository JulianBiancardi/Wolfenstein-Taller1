#ifndef CHEST_H
#define CHEST_H

#include "item.h"

class Chest : public Item {
 private:
 public:
  Chest(const Ray& position, unsigned int resource_id, unsigned int id);
  ~Chest();

  void use_on(Player& player);
};

#endif
