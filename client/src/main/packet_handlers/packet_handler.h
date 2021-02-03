#ifndef PACKET_HANDLER_H
#define PACKET_HANDLER_H

#include "../../../../common/src/main/packets/packet.h"

class PacketHandler {
 private:
 public:
  PacketHandler();
  ~PacketHandler();

  virtual void handle(Packet& packet) = 0;
};

#endif