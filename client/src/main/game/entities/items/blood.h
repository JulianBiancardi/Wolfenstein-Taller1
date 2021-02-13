#ifndef BLOOD_H
#define BLOOD_H

#include "item.h"

class Blood : public Item {
 private:
 public:
  Blood(const Ray& position, unsigned int resource_id, unsigned int id);
  ~Blood();

  void use_on(Player& player);
};

#endif
