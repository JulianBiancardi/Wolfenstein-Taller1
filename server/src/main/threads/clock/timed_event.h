#ifndef TIMED_EVENT_H
#define TIMED_EVENT_H

#include <chrono>
#include "../../../../common/src/main/packets/packet.h"
#include "../../../../common/src/main/data_structures/blocking_queue.h"

class TimedEvent {
 private:
  std::chrono::duration<double> initial_time;
  std::chrono::duration<double> remaining_time;
  bool should_delete;

 protected:
  BlockingQueue<Packet>& reception_queue;
  TimedEvent(double duration,
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
