//#include "game_test/gun_tests.h" TODO Solve bugs and include
#include "data_structures_tests/blocking_queue_tests.h"
#include "data_structures_tests/protected_queue_tests.h"
#include "mask_tests/box_mask_tests.h"
#include "mask_tests/circle_mask_tests.h"
#include "utils_tests/angle_tests.h"
#include "utils_tests/matrix_tests.h"
#include "utils_tests/point_tests.h"
#include "utils_tests/ray_tests.h"
#include "utils_tests/rectangle_tests.h"

int main(int argc, char **argv) {
  matrix_tests();
  point_tests();
  angle_tests();
  ray_tests();
  rectangle_tests();
  blocking_queue_tests();
  protected_queue_tests();
  circle_mask_tests();
  box_mask_tests();
  return 0;
}