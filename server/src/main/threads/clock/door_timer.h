#ifndef DOOR_TIMER_H
#define DOOR_TIMER_H

#include "timed_event.h"

class DoorTimer : public TimedEvent {
 public:
  DoorTimer();
  ~DoorTimer();

  void execute() override;
};

#endif
