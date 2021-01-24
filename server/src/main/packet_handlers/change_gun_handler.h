#ifndef CHANGE_GUN_HANDLER_H
#define CHANGE_GUN_HANDLER_H

#include "../../../../common/src/main/packets/packet.h"
#include "../client_manager.h"
#include "../match_manager.h"
#include "packet_handler.h"

class ChangeGunHandler : public PacketHandler {
 private:
 public:
  ChangeGunHandler();
  ~ChangeGunHandler();

  void handle(Packet& packet, ClientManager& client_manager,
              MatchManager& match_manager) override;
};

#endif
