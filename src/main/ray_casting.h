#ifndef RAY_CASTING_H
#define RAY_CASTING_H

#include "matrix.h"
#include "point.h"
#include "ray.h"

class RayCasting {
 private:
  Point static first_quad(Matrix<int>& map, Ray& ray);
  Point static second_quad(Matrix<int>& map, Ray& ray);
  Point static third_quad(Matrix<int>& map, Ray& ray);
  Point static forth_quad(Matrix<int>& map, Ray& ray);
  Point static horizontal_axis(Matrix<int>& map, Ray& ray);
  Point static vertical_axis(Matrix<int>& map, Ray& ray);

 public:
  RayCasting() = delete;
  ~RayCasting() = delete;

  Point static get_intersection(Matrix<int>& m, Ray& ray);
  double static get_scaling_factor(Ray& ray, Ray& player_direction,
                                   Point& intersection_point);
};

#endif
