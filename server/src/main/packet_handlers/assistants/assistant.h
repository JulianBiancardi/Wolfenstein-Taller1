#ifndef PACKET_HANDLER_ASSISTANT_H
#define PACKET_HANDLER_ASSISTANT_H

#include "../../../../../common/src/main/packets/packet.h"
#include "../../managers/client_manager.h"
#include "../../managers/match.h"

class PacketHandlerAssistant {
 private:
 public:
  PacketHandlerAssistant();
  ~PacketHandlerAssistant();

  virtual Packet build_packet(unsigned int player_id, unsigned char initial_gun,
                              Match& match) = 0;
};

#endif
