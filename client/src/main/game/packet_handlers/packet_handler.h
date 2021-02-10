#ifndef PACKET_HANDLER_H
#define PACKET_HANDLER_H

#include "../../../../../common/src/main/packets/packet.h"
#include "../../../../common/src/main/packets/packet.h"
#include "../audio/game_sound.h"
#include "../map/map.h"

class PacketHandler {
 private:
 public:
  PacketHandler();
  ~PacketHandler();

  virtual void handle(Packet &packet, Map &map, GameSound &sound) = 0;
};

#endif