#ifndef MATCH_START_HANDLER_H
#define MATCH_START_HANDLER_H

#include "../../../../common/src/main/packets/packet.h"
#include "../managers/client_manager.h"
#include "../managers/match_manager.h"
#include "packet_handler.h"

class MatchStartHandler : public PacketHandler {
 private:
 public:
  MatchStartHandler();
  ~MatchStartHandler();

  void handle(Packet& packet, ClientManager& client_manager,
              MatchManager& match_manager) override;
};

#endif