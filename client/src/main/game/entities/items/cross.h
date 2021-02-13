#ifndef CROSS_H
#define CROSS_H

#include "item.h"

class Cross : public Item {
 private:
 public:
  Cross(const Ray& position, unsigned int resource_id, unsigned int id);
  ~Cross();

  void use_on(Player& player);
};

#endif
