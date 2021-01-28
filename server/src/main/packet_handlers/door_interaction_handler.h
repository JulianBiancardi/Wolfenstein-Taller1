#ifndef DOOR_INTERACTION_HANDLER_H
#define DOOR_INTERACTION_HANDLER_H

#include "packet_handler.h"

class DoorInteractionHandler : public PacketHandler {
 private:
 public:
  DoorInteractionHandler();
  ~DoorInteractionHandler();

  void handle(Packet& packet, ClientManager& client_manager,
              MatchManager& match_manager) override;
};

#endif
