#include "clock_thread.h"

#include <chrono>
#include "door_timer.h"
#include "lock.h"
#include "../../../../common/src/main/packets/packing.h"

#define DOOR_TYPE 1

using namespace std::chrono;

ClockThread::ClockThread(unsigned int match_length,
                         BlockingQueue<Packet>& queue,
                         unsigned char match_id)
    : remaining_time(match_length),
      reception_queue(queue),
      match_id(match_id),
      allowed_to_run(true) {}

ClockThread::~ClockThread() {
  for (auto event : timed_events)
    delete event.second;
}

void ClockThread::update_timed_events() {
  Lock lock(this->mutex);
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
  size_t size = pack(data, "CC", GAME_OVER, &match_id);
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

    duration<double> seconds_spent = duration<double>(end - begin);

    std::this_thread::sleep_for(seconds(1) - seconds_spent);

    remaining_time--;

    if (remaining_time == seconds(0)) {
      allowed_to_run = false;
      end_game();
    }
  }
}

unsigned int get_door_id(unsigned int door_id) {
  return stoul(std::to_string(DOOR_TYPE) + std::to_string(door_id));
}

void ClockThread::add_door_timer(unsigned int door_id) {
  Lock lock(this->mutex);
  unsigned int id = get_door_id(door_id);

  if (timed_event_exist(id)) {
    timed_events.at(id)->reset();
  } else {
    timed_events.insert({id,
                         new DoorTimer(reception_queue, match_id, door_id)});
  }
}

void ClockThread::delete_door_timer(unsigned int door_id) {
  Lock lock(this->mutex);
  unsigned int id = get_door_id(door_id);

  if (timed_event_exist(id)) {
    delete timed_events.at(id);
    timed_events.erase(id);
  }
}
