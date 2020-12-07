#ifndef RAY_CASTING_H
#define RAY_CASTING_H

#include "map.h"
#include "utils/point.h"
#include "utils/ray.h"

class RayCasting {
 private:
  Point static first_quad(Map& map, Ray& ray);
  Point static second_quad(Map& map, Ray& ray);
  Point static third_quad(Map& map, Ray& ray);
  Point static forth_quad(Map& map, Ray& ray);
  Point static horizontal_axis(Map& map, Ray& ray);
  Point static vertical_axis(Map& map, Ray& ray);

 public:
  RayCasting() = delete;
  ~RayCasting() = delete;

  Point static get_intersection(Map& m, Ray& ray);
  double static get_scaling_factor(Ray& ray, Ray& player_direction,
                                   Point& intersection_point);
};

#endif
