#ifndef MOVE_HANDLER_H
#define MOVE_HANDLER_H

#include "../../../../common/src/main/packets/packet.h"
#include "../client_manager.h"
#include "../match_manager.h"
#include "packet_handler.h"

class MoveHandler : public PacketHandler {
 private:
 public:
  MoveHandler();
  ~MoveHandler();

  void handle(Packet& packet, ClientManager& client_manager,
              MatchManager& match_manager) override;
};

#endif
