#include "timed_event.h"

TimedEvent::TimedEvent(unsigned int duration,
                       BlockingQueue<Packet>& queue,
                       unsigned char match_id)
    : initial_time(duration),
      remaining_time(duration),
      reception_queue(queue),
      match_id(match_id),
      should_delete(false) {}

TimedEvent::~TimedEvent() = default;

void TimedEvent::update() {
  remaining_time--;

  if (remaining_time == 0) {
    execute();
    reset();
  }
}

bool TimedEvent::should_be_deleted() const { return should_delete; }

void TimedEvent::reset() { remaining_time = initial_time; }
