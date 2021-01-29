#ifndef SHOT_HANDLER_H
#define SHOT_HANDLER_H

#include "../../../../common/src/main/packets/packet.h"
#include "../managers/client_manager.h"
#include "../managers/match_manager.h"
#include "packet_handler.h"

class ShotHandler : public PacketHandler {
 private:
 public:
  ShotHandler();
  ~ShotHandler();

  void handle(Packet& packet, ClientManager& client_manager,
              MatchManager& match_manager) override;
};

#endif
