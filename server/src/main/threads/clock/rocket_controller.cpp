#include "rocket_controller.h"

#include "../../../../common/src/main/packets/packing.h"

RocketController::RocketController(BlockingQueue<Packet>& queue,
                                   unsigned char match_id,
                                   unsigned int rocket_id)
    : TimedEvent(1, queue, match_id), rocket_id(rocket_id) {}

RocketController::~RocketController() {}

void RocketController::execute() {
  unsigned char data[ROCKET_MOVE_SIZE];
  size_t size = pack(data, "CIC", ROCKET_MOVE, &rocket_id, &match_id);
  Packet packet(size, data);

  reception_queue.enqueue(packet);
}
