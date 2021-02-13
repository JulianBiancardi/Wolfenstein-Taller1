#ifndef OBJECT_H
#define OBJECT_H

#include "../../../../../common/src/main/utils/point.h"
#include "../../../../../common/src/main/utils/ray.h"
#include "drawable.h"

class Object : public Drawable {
 protected:
  unsigned int resource_id;
  Ray position;

 public:
  Object(const Ray& position, unsigned int resource_id);
  ~Object();

  int get_res_id() { return resource_id; }  // TODO Delete
  Point get_position() const;
  double get_angle() const;
  virtual Image* get_image(ResourceManager& resource_manager) override;
};

#endif
