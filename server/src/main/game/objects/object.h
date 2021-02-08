#ifndef SERVER_OBJECT_H
#define SERVER_OBJECT_H

#include "../../../../common/src/main/identifiable.h"
#include "../../../../common/src/main/utils/point.h"
#include "../../../../common/src/main/utils/ray.h"
#include "../collisions/mask.h"

class Object : public Identifiable {
 protected:
  Ray position;
  Mask* mask;
  Object(Point position, double angle, Mask* mask);
  Object(Point position, double angle, Mask* mask, int id);
  Object(Ray position, Mask* mask, int id);
  Object(Ray position, Mask* mask);

 public:
  virtual ~Object();
  bool occupies(const Point& where) const;
  Point get_position() const;
  double get_angle() const;
};

#endif
