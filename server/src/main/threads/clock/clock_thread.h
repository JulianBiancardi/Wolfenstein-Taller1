#ifndef CLOCK_THREAD_H
#define CLOCK_THREAD_H

#include <atomic>
#include <vector>
#include <mutex>

#include "../../../../../common/src/main/threads/thread.h"
#include "timed_event.h"

class ClockThread : public Thread {
 private:
  std::chrono::duration<double> remaining_time;
  std::atomic<bool> allowed_to_run;
  std::vector<TimedEvent*> timed_events;
  std::mutex mutex;
  void run() override;

  void update_timed_events();

 public:
  /* Match length is in seconds */
  explicit ClockThread(unsigned int match_length);

  ClockThread(const ClockThread&) = delete;
  ClockThread& operator=(const ClockThread&) = delete;

  ClockThread(ClockThread&& other) = delete;
  ClockThread& operator=(ClockThread&& other) = delete;

  ~ClockThread();

  void force_stop();
  void add_door_timer();
};

#endif
