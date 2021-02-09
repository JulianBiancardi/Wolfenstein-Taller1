#ifndef ROCKET_CONTROLLER_H
#define ROCKET_CONTROLLER_H

#include "timed_event.h"

class RocketController : public TimedEvent {
 private:
  unsigned int rocket_id;
  unsigned int player_id;

 public:
  RocketController(BlockingQueue<Packet>& queue,
                   unsigned char match_id,
                   unsigned int rocket_id,
                   unsigned int player_id);
  ~RocketController();

  void execute() override;
};

#endif
