#include "timed_event.h"

TimedEvent::TimedEvent(double duration)
    : remaining_time(duration), should_delete(false) {}

TimedEvent::~TimedEvent() = default;

void TimedEvent::update() {
  remaining_time--;

  if (remaining_time == std::chrono::duration<double>(0)) {
    execute();
    should_delete = true;
  }
}

bool TimedEvent::should_be_deleted() const {
  return should_delete;
}
