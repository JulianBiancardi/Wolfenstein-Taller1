#ifndef CLOCK_THREAD_H
#define CLOCK_THREAD_H

#include <atomic>
#include <mutex>
#include <unordered_map>

#include "../../../../../common/src/main/threads/thread.h"
#include "timed_event.h"

class ClockThread : public Thread {
 private:
  int remaining_tics;
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
  explicit ClockThread(unsigned int match_length, BlockingQueue<Packet>& queue,
                       unsigned char match_id);

  ClockThread(const ClockThread&) = delete;
  ClockThread& operator=(const ClockThread&) = delete;

  ClockThread(ClockThread&& other) = delete;
  ClockThread& operator=(ClockThread&& other) = delete;

  ~ClockThread();

  void force_stop();

  /* Adds door automatic close timer, if it already exists, it is reset */
  void add_door_timer(std::pair<unsigned int, unsigned int> door_cell);

  /* Deletes door automatic close timer */
  void delete_door_timer(unsigned int door_id);

  /* Adds rocket movement controller */
  void add_rocket_controller(unsigned int rocket_id, unsigned int player_id);

  /* Deletes rocket movement controller */
  void delete_rocket_controller(unsigned int rocket_id);
};

#endif
