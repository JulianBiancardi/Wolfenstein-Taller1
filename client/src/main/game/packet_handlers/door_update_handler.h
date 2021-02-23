#ifndef DOOR_UPDATE_HANDLER_H
#define DOOR_UPDATE_HANDLER_H

#include "../../../../../common/src/main/packets/packet.h"
#include "../audio/game_sound.h"
#include "../map/map.h"
#include "packet_handler.h"

class DoorUpdateHandler : public PacketHandler {
 private:
 public:
  DoorUpdateHandler();
  ~DoorUpdateHandler();

  /* Returns if game should continue or not */
  bool handle(Packet& packet, Map& map, GameSound& sound) override;
};

#endif