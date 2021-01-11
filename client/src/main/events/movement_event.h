#ifndef WOLFENSTEIN_TALLER1_CLIENT_SRC_MAIN_EVENTS_MOVEMENT_EVENT_H_
#define WOLFENSTEIN_TALLER1_CLIENT_SRC_MAIN_EVENTS_MOVEMENT_EVENT_H_

#include "../../../../common/src/main/utils/point.h"
#include "../caster.h"
#include "event.h"

class MovementEvent : public Event {
 private:
  const int &id;
  const Point &new_origin;

 public:
  MovementEvent(const int &id, const Point &new_origin);
  void process();
};

#endif  // WOLFENSTEIN_TALLER1_CLIENT_SRC_MAIN_EVENTS_MOVEMENT_EVENT_H_
