#ifndef PACKET_HANDLER_H
#define PACKET_HANDLER_H

#include "../../../../common/src/main/packets/packet.h"
#include "../managers/client_manager.h"
#include "../managers/match_manager.h"

class PacketHandler {
 private:
 protected:
  void consequent_grab(unsigned int player_id, Match& match,
                       ClientManager& client_manager);
  void game_over(Match& match, ClientManager& client_manager);

 public:
  PacketHandler();
  ~PacketHandler();

  virtual void handle(Packet& packet, ClientManager& client_manager,
                      MatchManager& match_manager) = 0;
};

#endif