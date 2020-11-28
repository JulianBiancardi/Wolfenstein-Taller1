#ifndef RAY_CASTING_H
#define RAY_CASTING_H

#include <stdlib.h>

#include "matrix.h"
#include "point.h"
#include "ray.h"

class RayCasting {
 private:
  /* data */
 public:
  RayCasting(/* args */);
  ~RayCasting();

  template <size_t X, size_t Y>
  Point cast(Matrix<int>& m, Ray& ray);
};

#endif
