#include "clock_tests.h"

#include "../tests_setup.h"
#include "../../main/threads/clock/clock_thread.h"
#include "../../../../common/src/main/config_loader.h"
#include <chrono>
#include <cmath>

using namespace std::chrono;

int static clock_countdown_works();
int static clock_countdown_with_an_event_works();
int static clock_countdown_with_various_event_works();
int static clock_deletes_timed_events_finished();

bool time_compare(double x, double y, double epsilon) {
  return fabs(x - y) < epsilon;
}

void clock_tests() {
  begin_tests("CLOCK");

  print_test("El clock termina de ejecutarse cuando no queda tiempo",
             clock_countdown_works, NO_ERROR);
  print_test("Un clock con un evento por tiempo termina cuando debe",
             clock_countdown_with_an_event_works, NO_ERROR);
  print_test("Un clock con varios eventos por tiempo termina cuando debe",
             clock_countdown_with_various_event_works, NO_ERROR);
  print_test("El clock elimina los eventos que ya fueron ejecutados",
             clock_deletes_timed_events_finished, NO_ERROR);

  end_tests();
}

int static clock_countdown_works() {
  ClockThread thread(2);

  steady_clock::time_point begin = steady_clock::now();

  thread.start();
  thread.join();

  steady_clock::time_point end = steady_clock::now();

  double seconds_spent = duration<double>(end - begin).count();

  if (time_compare(seconds_spent, 2, 0.1))
    return NO_ERROR;

  return ERROR;
}

int static clock_countdown_with_an_event_works() {
  ClockThread thread(CL::door_timer / 2);

  thread.add_door_timer();

  steady_clock::time_point begin = steady_clock::now();

  thread.start();
  thread.join();

  steady_clock::time_point end = steady_clock::now();

  double seconds_spent = duration<double>(end - begin).count();

  if (time_compare(seconds_spent, (unsigned int) (CL::door_timer / 2), 0.1))
    return NO_ERROR;

  return ERROR;
}

int static clock_countdown_with_various_event_works() {
  ClockThread thread(CL::door_timer / 2);

  for (int i = 0; i < 10; i++) {
    thread.add_door_timer();
  }

  steady_clock::time_point begin = steady_clock::now();

  thread.start();
  thread.join();

  steady_clock::time_point end = steady_clock::now();

  double seconds_spent = duration<double>(end - begin).count();

  if (time_compare(seconds_spent, (unsigned int) (CL::door_timer / 2), 0.1))
    return NO_ERROR;

  return ERROR;
}

int static clock_deletes_timed_events_finished() {
  ClockThread thread(2 * CL::door_timer);

  for (int i = 0; i < 5; i++) {
    thread.add_door_timer();
  }

  steady_clock::time_point begin = steady_clock::now();

  thread.start();
  thread.join();

  steady_clock::time_point end = steady_clock::now();

  double seconds_spent = duration<double>(end - begin).count();

  if (time_compare(seconds_spent, (unsigned int) (2 * CL::door_timer), 0.1))
    return NO_ERROR;

  return ERROR;
}
