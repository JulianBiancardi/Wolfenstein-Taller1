#include "rocket_controller.h"

#include "../../../../common/src/main/packets/packing.h"

RocketController::RocketController(BlockingQueue<Packet>& queue,
                                   unsigned char match_id,
                                   unsigned int rocket_id,
                                   unsigned int player_id)
    : TimedEvent(1, queue, match_id), rocket_id(rocket_id),
      player_id(player_id) {}

RocketController::~RocketController() {}

void RocketController::execute() {
  unsigned char data[ROCKET_MOVE_SIZE];
  size_t size = pack(data, "CICI", ROCKET_MOVE, &rocket_id, &match_id,
                     &player_id);
  Packet packet(size, data);

  reception_queue.enqueue(packet);
}
