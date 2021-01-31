#include "door_timer.h"

#include <thread> // REMOVE
#include "../../../../../common/src/main/config_loader.h"

DoorTimer::DoorTimer() : TimedEvent(CL::door_timer) {}

DoorTimer::~DoorTimer() {}

void DoorTimer::execute() {
  //match.enque_event(door_close)
  std::this_thread::sleep_for(std::chrono::duration<double>(0.05));
}
