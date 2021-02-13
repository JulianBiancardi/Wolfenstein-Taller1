#ifndef KEY_H
#define KEY_H

#include "item.h"

class Key : public Item {
 private:
 public:
  Key(const Ray& position, unsigned int resource_id, unsigned int id);
  ~Key();

  void use_on(Player& player);
};

#endif
