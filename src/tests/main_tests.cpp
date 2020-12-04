//#include "game_test/gun_tests.h"
#include "matrix_tests.h"
#include "point_tests.h"
#include "ray_tests.h"

int main(int argc, char** argv) {
  matrix_tests();
  point_tests();
  ray_tests();
  // gun_tests();
  return 0;
}