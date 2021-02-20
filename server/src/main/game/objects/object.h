#ifndef SERVER_OBJECT_H
#define SERVER_OBJECT_H

#include "../../../../common/src/main/identifiable.h"
#include "../../../../common/src/main/utils/point.h"
#include "../../../../common/src/main/utils/ray.h"
#include "../collisions/mask.h"

class Object {
 protected:
  Ray position;
  Mask* mask;

  Object(const Point& position, double angle, Mask* mask);
  Object(const Ray& position, Mask* mask);

  Object(const Object& other);

 public:
  virtual ~Object();

  /* Returns if the object occupies the point received */
  bool occupies(const Point& where) const;

  /* Returns object's position */
  Point get_position() const;

  /* Returns object's angle */
  double get_angle() const;
};

#endif
