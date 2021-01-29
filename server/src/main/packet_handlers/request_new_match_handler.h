#ifndef REQUEST_NEW_MATCH_HANDLER_H
#define REQUEST_NEW_MATCH_HANDLER_H

#include "../../../../common/src/main/packets/packet.h"
#include "../managers/client_manager.h"
#include "../managers/match_manager.h"
#include "packet_handler.h"

class RequestNewMatchHandler : public PacketHandler {
 private:
 public:
  RequestNewMatchHandler();
  ~RequestNewMatchHandler();

  void handle(Packet& packet, ClientManager& client_manager,
              MatchManager& match_manager) override;
};

#endif
