#ifndef CUP_H
#define CUP_H

#include "item.h"

class Cup : public Item {
 private:
 public:
  Cup(const Ray& position, unsigned int resource_id, unsigned int id);
  ~Cup();

  void use_on(Player& player);
};

#endif
