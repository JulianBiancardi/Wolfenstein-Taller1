#ifndef JOIN_MATCH_HANDLER_H
#define JOIN_MATCH_HANDLER_H

#include "../../../../common/src/main/packets/packet.h"
#include "../client_manager.h"
#include "../match_manager.h"
#include "packet_handler.h"

class JoinMatchHandler : public PacketHandler {
 private:
 public:
  JoinMatchHandler();
  ~JoinMatchHandler();

  void handle(Packet& packet, ClientManager& client_manager,
              MatchManager& match_manager) override;
};

#endif