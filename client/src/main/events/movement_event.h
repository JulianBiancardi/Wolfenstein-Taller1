#ifndef WOLFENSTEIN_TALLER1_CLIENT_SRC_MAIN_EVENTS_MOVEMENT_EVENT_H_
#define WOLFENSTEIN_TALLER1_CLIENT_SRC_MAIN_EVENTS_MOVEMENT_EVENT_H_

#include "event.h"
#include "../caster.h"

class MovementEvent : public Event {
 private:
  const int &id;
  const Point &new_origin;

 public:
  MovementEvent(const int &id, const Point &new_origin);
 void process();

};

#endif //WOLFENSTEIN_TALLER1_CLIENT_SRC_MAIN_EVENTS_MOVEMENT_EVENT_H_
