#ifndef MEDKIT_H
#define MEDKIT_H

#include "../identifiable_object.h"
#include "item.h"

class Medkit : public Item, public IdentifiableObject {
 private:
  /* data */
 public:
  Medkit(Ray& position, unsigned int id);
  ~Medkit();

  Image* get_image(ResourceManager& resource_manager);

  void use_on(Player& player);
};

#endif
