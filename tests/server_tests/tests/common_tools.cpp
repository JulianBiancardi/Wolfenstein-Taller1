#include "common_tools.h"

#include <cmath>

bool double_compare(double x, double y, double epsilon) {
  return fabs(x - y) < epsilon;
}
