#ifndef CLOCK_THREAD_H
#define CLOCK_THREAD_H

#include <atomic>
#include <unordered_map>
#include <mutex>

#include "../../../../../common/src/main/threads/thread.h"
#include "timed_event.h"

class ClockThread : public Thread {
 private:
  std::chrono::duration<double> remaining_time;
  std::atomic<bool> allowed_to_run;
  std::unordered_map<unsigned int, TimedEvent*> timed_events;
  std::mutex mutex;
  BlockingQueue<Packet>& reception_queue;
  unsigned char match_id;
  void run() override;

  void update_timed_events();
  void end_game();
  bool timed_event_exist(unsigned int id);

 public:
  /* Match length is in seconds */
  explicit ClockThread(unsigned int match_length,
                       BlockingQueue<Packet>& queue,
                       unsigned char match_id);

  ClockThread(const ClockThread&) = delete;
  ClockThread& operator=(const ClockThread&) = delete;

  ClockThread(ClockThread&& other) = delete;
  ClockThread& operator=(ClockThread&& other) = delete;

  ~ClockThread();

  void force_stop();
  void add_door_timer(unsigned int door_id);
  void delete_door_timer(unsigned int door_id);
};

#endif
