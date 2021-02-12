#ifndef IDENTIFIABLE_OBJECT_H
#define IDENTIFIABLE_OBJECT_H

#include "../../../../../common/src/main/identifiable.h"
#include "../../../../../common/src/main/utils/point.h"
#include "../../../../../common/src/main/utils/ray.h"
#include "object.h"

class IdentifiableObject : public Identifiable, public Object {
 public:
  IdentifiableObject(unsigned char res_id, double x_pos, double y_pos,
                     double angle, int id);
  IdentifiableObject(unsigned char res_id, Point position, double angle,
                     int id);
  IdentifiableObject(unsigned char res_id, Ray position, int id);
  ~IdentifiableObject();

  void domr();
};

#endif