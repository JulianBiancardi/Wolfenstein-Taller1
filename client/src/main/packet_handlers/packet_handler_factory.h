#ifndef PACKET_HANDLER_FACTORY_H
#define PACKET_HANDLER_FACTORY_H

#include "../../../../common/src/main/packets/packet.h"
#include "packet_handler.h"

class PacketHandlerFactory {
 private:
 public:
  PacketHandlerFactory() = delete;
  ~PacketHandlerFactory() = delete;

  static PacketHandler* build(Packet& packet);
};

#endif
