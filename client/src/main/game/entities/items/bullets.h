#ifndef BULLETS_H
#define BULLETS_H

#include "item.h"

class Bullets : public Item {
 private:
 public:
  Bullets(const Ray& position, unsigned int resource_id, unsigned int id);
  ~Bullets();

  void use_on(Player& player);
};

#endif
