#ifndef TIMED_EVENT_H
#define TIMED_EVENT_H

#include <chrono>
#include "../../../../common/src/main/packets/packet.h"
#include "../../../../common/src/main/data_structures/blocking_queue.h"

#define TICS_PER_SECOND 30.0

class TimedEvent {
 private:
  unsigned int initial_time;
  unsigned int remaining_time;
  bool should_delete;

 protected:
  BlockingQueue<Packet>& reception_queue;
  TimedEvent(unsigned int duration,
             BlockingQueue<Packet>& queue,
             unsigned char match_id);

  unsigned char match_id;

 public:
  void update();
  virtual void execute() = 0;
  bool should_be_deleted() const;
  void reset();
  virtual ~TimedEvent();
};

#endif
