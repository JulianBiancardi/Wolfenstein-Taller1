#ifndef END_OF_CONNECTION_HANDLER_H
#define END_OF_CONNECTION_HANDLER_H

#include "../../../../common/src/main/packets/packet.h"
#include "../client_manager.h"
#include "../match_manager.h"
#include "packet_handler.h"

class EndOfConnectionHandler : public PacketHandler {
 private:
 public:
  EndOfConnectionHandler();
  ~EndOfConnectionHandler();

  void handle(Packet& packet, ClientManager& client_manager,
              MatchManager& match_manager) override;
};

#endif