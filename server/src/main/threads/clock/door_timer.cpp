#include "door_timer.h"

#include "../../../../../common/src/main/config_loader.h"
#include "../../../../common/src/main/packets/packing.h"

DoorTimer::DoorTimer(BlockingQueue<Packet>& queue,
                     unsigned char match_id,
                     unsigned int door_id,
                     const std::pair<unsigned int, unsigned int>& cell)
    : TimedEvent(CL::door_timer * TICS_PER_SECOND, queue, match_id),
      door_id(door_id), cell(cell) {}

DoorTimer::~DoorTimer() = default;

void DoorTimer::execute() {
  unsigned char data[CLOSE_DOOR_SIZE];
  size_t size = pack(data, "CIIC", CLOSE_DOOR, cell.first, cell.second,
                     match_id);
  Packet packet(size, data);

  reception_queue.enqueue(packet);
}
