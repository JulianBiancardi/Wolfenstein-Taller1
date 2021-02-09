#ifndef OBJECT_H
#define OBJECT_H

#include "../../../common/src/main/identifiable.h"
#include "../../../common/src/main/utils/point.h"
#include "../../../common/src/main/utils/ray.h"

class Object : public Identifiable {
 protected:
  unsigned char res_id;
  Ray position;

 public:
  Object(unsigned char res_id, double x_pos, double y_pos, double angle);
  Object(unsigned char res_id, Point position, double angle);
  Object(unsigned char res_id, Ray position);
  Object(unsigned char res_id, double x_pos, double y_pos, double angle,
         int id);
  Object(unsigned char res_id, Point position, double angle, int id);
  Object(unsigned char res_id, Ray position, int id);
  ~Object();

  unsigned char get_res_id();
  Point get_position() const;
  double get_angle() const;
};

#endif
