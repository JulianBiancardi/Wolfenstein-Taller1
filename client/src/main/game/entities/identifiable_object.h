#ifndef IDENTIFIABLE_OBJECT_H
#define IDENTIFIABLE_OBJECT_H

#include "../../../../../common/src/main/identifiable.h"
#include "../../../../../common/src/main/utils/point.h"
#include "../../../../../common/src/main/utils/ray.h"
#include "object.h"

class IdentifiableObject : public Identifiable, public Object {
 public:
  IdentifiableObject(const Ray& position, int id);
  ~IdentifiableObject();
};

#endif