#include "clock_thread.h"

#include <chrono>
#include "door_timer.h"
#include "lock.h"

using namespace std::chrono;

ClockThread::ClockThread(unsigned int match_length)
    : remaining_time(match_length), allowed_to_run(true) {}

ClockThread::~ClockThread() { for (auto event : timed_events) delete event; }

void ClockThread::update_timed_events() {
  for (auto it = timed_events.begin(); it != timed_events.end(); it++) {
    (*it)->update();

    if ((*it)->should_be_deleted()) {
      delete (*it);
      it = --timed_events.erase(it);
    }
  }
}

void ClockThread::force_stop() { allowed_to_run = false; }

void ClockThread::run() {
  while (allowed_to_run) {
    steady_clock::time_point begin = steady_clock::now();

    update_timed_events();

    steady_clock::time_point end = steady_clock::now();

    duration<double> seconds_spent = duration<double>(end - begin);

    std::this_thread::sleep_for(seconds(1) - seconds_spent);

    remaining_time--;

    if (remaining_time == seconds(0)) {
      allowed_to_run = false;
    }
  }
}

void ClockThread::add_door_timer() {
  Lock lock(this->mutex);
  timed_events.push_back(new DoorTimer());
}
