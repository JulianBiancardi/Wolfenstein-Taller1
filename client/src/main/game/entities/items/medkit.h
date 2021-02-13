#ifndef MEDKIT_H
#define MEDKIT_H

#include "item.h"

class Medkit : public Item {
 private:
 public:
  Medkit(const Ray& position, unsigned int resource_id, unsigned int id);
  ~Medkit();

  void use_on(Player& player);
};

#endif
