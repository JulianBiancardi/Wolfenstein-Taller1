#ifndef OBJECT_H
#define OBJECT_H

#include "../../../../../common/src/main/utils/point.h"
#include "../../../../../common/src/main/utils/ray.h"
#include "drawable.h"

class Object : public Drawable {
 protected:
  Ray position;

 public:
  Object(const Ray& position);
  ~Object();

  Point get_position() const;
  double get_angle() const;
  Image* get_image(ResourceManager& resource_manager) override;
};

#endif
