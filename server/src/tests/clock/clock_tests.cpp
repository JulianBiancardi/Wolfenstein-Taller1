#include "clock_tests.h"

#include "../tests_setup.h"
#include "../../main/threads/clock/clock_thread.h"
#include "../../../../common/src/main/config_loader.h"
#include "../../main/managers/match.h"
#include "../../main/managers/client_manager.h"
#include "../../../../common/src/main/packets/packing.h"
#include <chrono>
#include <cmath>

#define TEST_MAP_WITH_DOOR "test_map_with_door"
#define TEST_MAP_WITH_MULTIPLE_DOORS "test_map_with_multiple_doors"

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
  ClientManager manager;
  std::string map_name(TEST_MAP_WITH_DOOR);
  Match match(1, map_name);

  ClockThread thread(2, manager.get_reception_queue(), 1);

  steady_clock::time_point begin = steady_clock::now();

  thread.start();
  thread.join();

  steady_clock::time_point end = steady_clock::now();

  double seconds_spent = duration<double>(end - begin).count();

  if (!time_compare(seconds_spent, 2, 0.1))
    return ERROR;

  /*Packet packet;
  manager.get_reception_queue().dequeue(packet);

  unsigned char type;
  unsigned char match_id;
  unpack(packet.get_data(), "CC", &type, &match_id);

  if (type != GAME_OVER || match_id != 1)
    return ERROR;*/

  return NO_ERROR;
}

int static clock_countdown_with_an_event_works() {
  ClientManager manager;
  std::string map_name(TEST_MAP_WITH_DOOR);
  Match match(1, map_name);

  ClockThread thread((unsigned int) (CL::door_timer / 2),
                     manager.get_reception_queue(), 1);

  thread.add_door_timer(1);

  steady_clock::time_point begin = steady_clock::now();

  thread.start();
  thread.join();

  steady_clock::time_point end = steady_clock::now();

  double seconds_spent = duration<double>(end - begin).count();

  if (!time_compare(seconds_spent, (unsigned int) (CL::door_timer / 2), 0.1))
    return ERROR;

  /*Packet packet;
  manager.get_reception_queue().dequeue(packet);

  unsigned char type;
  unsigned char match_id;
  unpack(packet.get_data(), "CC", &type, &match_id);

  if (type != GAME_OVER || match_id != 1)
    return ERROR;*/

  return NO_ERROR;
}

int static clock_countdown_with_various_event_works() {
  ClientManager manager;
  std::string map_name(TEST_MAP_WITH_MULTIPLE_DOORS);
  Match match(1, map_name);

  ClockThread thread((unsigned int) (CL::door_timer / 2),
                     manager.get_reception_queue(), 1);

  for (int i = 1; i < 6; i++) {
    thread.add_door_timer(i);
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
  ClientManager manager;
  std::string map_name(TEST_MAP_WITH_MULTIPLE_DOORS);
  Match match(1, map_name);

  ClockThread thread((unsigned int) (CL::door_timer * 2),
                     manager.get_reception_queue(), 1);

  for (int i = 1; i < 6; i++) {
    thread.add_door_timer(i);
  }

  steady_clock::time_point begin = steady_clock::now();

  thread.start();
  thread.join();

  steady_clock::time_point end = steady_clock::now();

  double seconds_spent = duration<double>(end - begin).count();

  if (time_compare(seconds_spent, (unsigned int) (CL::door_timer * 2), 0.1))
    return NO_ERROR;

  return ERROR;
}
