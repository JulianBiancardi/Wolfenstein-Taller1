#ifndef MEDKIT_H
#define MEDKIT_H

#include "../identifiable_object.h"
#include "item.h"

class Medkit : public Item {
 private:
  /* data */
 public:
  Medkit();
  ~Medkit();
};

Medkit::Medkit(/* args */) {}

Medkit::~Medkit() {}

#endif
