#ifndef OBJECT_H
#define OBJECT_H

#include "../../../../../common/src/main/utils/point.h"
#include "../../../../../common/src/main/utils/ray.h"
#include "drawable.h"

class Object : public Drawable {
 protected:
  unsigned char res_id;
  Ray position;

 public:
  Object(unsigned char res_id, Ray position);
  ~Object();

  unsigned char get_res_id();
  Point get_position() const;
  double get_angle() const;
  unsigned char get_type() const;
  Image* get_image(ResourceManager& resource_manager) override;
};

#endif
