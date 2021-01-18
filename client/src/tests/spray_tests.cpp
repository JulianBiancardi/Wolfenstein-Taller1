#include "spray_tests.h"

#include <cmath>
#include <vector>

#include "../main/guns/spray.h"
#include "tests_setup.h"

int static creation_test();
int static edges_test();
int static mean_test();
int static probability_test();

void spray_tests() {
  begin_tests("SPRAY");

  print_test("El spray se crea correctamente", creation_test, NO_ERROR);
  print_test("El spray devuelve valores entre sus bordes", edges_test,
             NO_ERROR);
  print_test("El spray devuelve valores con media 0", mean_test, NO_ERROR);
  print_test("El spray devuelve valores con distribución normal",
             probability_test, NO_ERROR);

  end_tests();
}

int static creation_test() {
  Spray spr1(0.174533, 0.1);
  Spray spr2(0.2, 0.5);
  Spray spr3(0.15, 0.25);
  return NO_ERROR;
}

int static edges_test() {
  Spray spr(0.2, 0.5);
  for (int i = 0; i < 100; i++) {
    double offset = spr();
    if (offset > 0.1) {
      return ERROR;
    }
  }
  return NO_ERROR;
}

int static mean_test() {
  Spray spr(0.2, 0.1);
  std::vector<double> offsets;
  offsets.resize(100);
  for (int i = 0; i < 100; i++) {
    offsets.push_back(spr());
  }

  double avg;
  for (int i = 0; i < 100; i++) {
    avg += offsets[i];
  }
  avg = avg / 100;

  /* Arbitrarily chosen number.
   * Given 100 numbers, it's nearly impossible this test fails,
   * unless spray is working badly.
   */
  if (fabs(avg) > 0.1) {
    return ERROR;
  }
  return NO_ERROR;
}

int static probability_test() {
  Spray spr(10, 1);
  std::vector<int> buckets_counter;
  buckets_counter.resize(5);
  for (int i = 0; i < 5; i++) {
    buckets_counter[i] = 0;
  }

  for (int i = 0; i < 100; i++) {
    ++buckets_counter[abs((int)spr())];
  }

  /* The bucket should have caught 68% of the values.
   * This is a generous assumption
   */
  if (buckets_counter[0] < 40 || buckets_counter[0] > 90) {
    return ERROR;
  }
  // 26% for this one
  if (buckets_counter[1] < 10 || buckets_counter[1] > 40) {
    return ERROR;
  }
  return NO_ERROR;
}