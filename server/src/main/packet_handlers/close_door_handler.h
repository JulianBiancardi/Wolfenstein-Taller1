#ifndef CLOSE_DOOR_HANDLER_H
#define CLOSE_DOOR_HANDLER_H

#include "../managers/client_manager.h"
#include "../managers/match_manager.h"
#include "packet_handler.h"

class CloseDoorHandler : public PacketHandler {
 private:
 public:
  CloseDoorHandler();
  ~CloseDoorHandler();

  void handle(Packet& packet, ClientManager& client_manager,
              MatchManager& match_manager) override;
};

#endif
