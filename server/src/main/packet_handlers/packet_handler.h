#ifndef PACKET_HANDLER_H
#define PACKET_HANDLER_H

#include "../../../../common/src/main/packets/packet.h"
#include "../client_manager.h"
#include "../match_manager.h"

class PacketHandler {
 private:
 public:
  PacketHandler() {}
  ~PacketHandler() {}

  virtual void handle(Packet& packet, ClientManager& client_manager,
                      MatchManager& match_manager) = 0;
};

#endif