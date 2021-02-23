#ifndef DOOR_TIMER_H
#define DOOR_TIMER_H

#include "timed_event.h"

class DoorTimer : public TimedEvent {
 private:
  unsigned int door_id;
  std::pair<unsigned int, unsigned int> cell;

 public:
  DoorTimer(BlockingQueue<Packet>& queue,
            unsigned char match_id,
            unsigned int door_id,
            const std::pair<unsigned int, unsigned int>& cell);
  ~DoorTimer();

  void execute() override;
};

#endif
