#include "clock_thread.h"

#include <chrono>
#include <iostream>
#include "door_timer.h"
#include "rocket_controller.h"
#include "../../../../common/src/main/packets/packing.h"

#define SECONDS_PER_TICS 1 / TICS_PER_SECOND

#define DOOR_TYPE 1
#define ROCKET_TYPE 2

using namespace std::chrono;

ClockThread::ClockThread(unsigned int match_length,
                         BlockingQueue<Packet>& queue,
                         unsigned char match_id)
    : remaining_tics(match_length * TICS_PER_SECOND),
      reception_queue(queue),
      match_id(match_id),
      allowed_to_run(true) {}

ClockThread::~ClockThread() {
  for (auto event : timed_events)
    delete event.second;
}

void ClockThread::update_timed_events() {
  const std::lock_guard<std::mutex> lock(this->mutex);
  for (auto it = timed_events.begin(); it != timed_events.end();) {
    (*it).second->update();

    if ((*it).second->should_be_deleted()) {
      delete (*it).second;
      it = timed_events.erase(it);
    } else {
      it++;
    }
  }
}

void ClockThread::end_game() {
  unsigned char data[GAME_OVER_SIZE];
  size_t size = pack(data, "CI", GAME_OVER, match_id);
  Packet packet(size, data);

  reception_queue.enqueue(packet);
}

bool ClockThread::timed_event_exist(unsigned int id) {
  return timed_events.find(id) != timed_events.end();
}

void ClockThread::force_stop() { allowed_to_run = false; }

void ClockThread::run() {
  while (allowed_to_run) {
    steady_clock::time_point begin = steady_clock::now();
    update_timed_events();
    steady_clock::time_point end = steady_clock::now();

    double seconds_spent = duration<double>(end - begin).count();
    double tics_spent = seconds_spent * TICS_PER_SECOND;

    if (tics_spent >= 1) {
      remaining_tics -= (int) tics_spent;
      tics_spent = tics_spent - (int) tics_spent;
    }

    double seconds_to_sleep = (1 - tics_spent) * SECONDS_PER_TICS;
    std::this_thread::sleep_for(duration<double>(seconds_to_sleep));

    remaining_tics--;

    if (remaining_tics <= 0) {
      allowed_to_run = false;
      end_game();
    }
  }
}

unsigned int get_door_id(unsigned int door_id) {
  return stoul(std::to_string(DOOR_TYPE) + std::to_string(door_id));
}

void ClockThread::add_door_timer(unsigned int door_id) {
  const std::lock_guard<std::mutex> lock(this->mutex);
  unsigned int id = get_door_id(door_id);

  if (timed_event_exist(id)) {
    timed_events.at(id)->reset();
  } else {
    timed_events.insert({id,
                         new DoorTimer(reception_queue, match_id, door_id)});
  }
}

void ClockThread::delete_door_timer(unsigned int door_id) {
  const std::lock_guard<std::mutex> lock(this->mutex);
  unsigned int id = get_door_id(door_id);

  if (timed_event_exist(id)) {
    delete timed_events.at(id);
    timed_events.erase(id);
  }
}

unsigned int get_rocket_id(unsigned int rocket_id) {
  return stoul(std::to_string(ROCKET_TYPE) + std::to_string(rocket_id));
}

void ClockThread::add_rocket_controller(unsigned int rocket_id,
                                        unsigned int player_id) {
  const std::lock_guard<std::mutex> lock(this->mutex);
  unsigned int id = get_rocket_id(rocket_id);

  if (timed_event_exist(id)) {
    timed_events.at(id)->reset();
  } else {
    timed_events.insert({id, new RocketController(reception_queue,
                                                  match_id,
                                                  rocket_id,
                                                  player_id)});
  }
}

void ClockThread::delete_rocket_controller(unsigned int rocket_id) {
  const std::lock_guard<std::mutex> lock(this->mutex);
  unsigned int id = get_rocket_id(rocket_id);

  if (timed_event_exist(id)) {
    delete timed_events.at(id);
    timed_events.erase(id);
  }
}
