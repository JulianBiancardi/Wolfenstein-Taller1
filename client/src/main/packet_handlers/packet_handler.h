#ifndef PACKET_HANDLER_H
#define PACKET_HANDLER_H

#include "../../../../common/src/main/packets/packet.h"
#include "../map.h"

class PacketHandler {
 private:
 public:
  PacketHandler();
  ~PacketHandler();

  virtual void handle(Packet& packet, Map& map) = 0;
};

#endif