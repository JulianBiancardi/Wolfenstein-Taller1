#ifndef MOVEMENT_EVENT_H
#define MOVEMENT_EVENT_H

#include "event.h"

class MovementEvent : private Event {
 private:
 public:
  MovementEvent();
  ~MovementEvent();

  void operator()();
};

MovementEvent::MovementEvent(/* args */) {}

MovementEvent::~MovementEvent() {}

void MovementEvent::operator()() {}

#endif
