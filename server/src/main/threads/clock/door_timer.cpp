#include "door_timer.h"

#include "../../../../../common/src/main/config_loader.h"
#include "../../../../common/src/main/packets/packing.h"

DoorTimer::DoorTimer(BlockingQueue<Packet>& queue,
                     unsigned char match_id,
                     unsigned int door_id)
    : TimedEvent(CL::door_timer, queue, match_id), door_id(door_id) {}

DoorTimer::~DoorTimer() {}

void DoorTimer::execute() {
  unsigned char data[CLOSE_DOOR_SIZE];
  size_t size = pack(data, "CCI", CLOSE_DOOR, &match_id, &door_id);
  Packet packet(size, data);

  reception_queue.enqueue(packet);
}
