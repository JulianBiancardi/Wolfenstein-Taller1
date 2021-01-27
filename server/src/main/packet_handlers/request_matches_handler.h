#ifndef REQUEST_MATCHES_HANDLER_H
#define REQUEST_MATCHES_HANDLER_H

#include "../../../../common/src/main/packets/packet.h"
#include "../client_manager.h"
#include "../match_manager.h"
#include "packet_handler.h"

class RequestMatchesHandler : public PacketHandler {
 private:
 public:
  RequestMatchesHandler();
  ~RequestMatchesHandler();

  void handle(Packet& packet, ClientManager& client_manager,
              MatchManager& match_manager) override;
};

#endif
