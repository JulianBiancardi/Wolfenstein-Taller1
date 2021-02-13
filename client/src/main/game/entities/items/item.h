#ifndef ITEM_H
#define ITEM_H

#include "../identifiable_object.h"
#include "../player.h"

class Item : public IdentifiableObject {
 private:
 public:
  Item(const Ray& position, unsigned int resource_id, unsigned int id);
  ~Item();

  virtual void use_on(Player& player) = 0;
};

#endif
