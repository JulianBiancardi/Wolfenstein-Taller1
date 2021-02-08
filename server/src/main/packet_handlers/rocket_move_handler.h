#ifndef ROCKET_MOVE_HANDLER_H
#define ROCKET_MOVE_HANDLER_H

#include "../../../../common/src/main/packets/packet.h"
#include "../managers/client_manager.h"
#include "../managers/match_manager.h"
#include "packet_handler.h"

class RocketMoveHandler : public PacketHandler {
 private:
 public:
  RocketMoveHandler();
  ~RocketMoveHandler();

  void handle(Packet& packet, ClientManager& client_manager,
              MatchManager& match_manager) override;
};

#endif
