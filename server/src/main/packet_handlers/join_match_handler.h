#ifndef JOIN_MATCH_HANDLER_H
#define JOIN_MATCH_HANDLER_H

#include "../../../../common/src/main/packets/packet.h"
#include "../managers/client_manager.h"
#include "../managers/match_manager.h"
#include "packet_handler.h"

class JoinMatchHandler : public PacketHandler {
 private:
  void notify_spawn(unsigned int player_id, unsigned char match_id,
                    ClientManager& client_manager, MatchManager& match_manager);
  void notify_all_spawns(unsigned int player_id, unsigned char match_id,
                         ClientManager& client_manager,
                         MatchManager& match_manager);

 public:
  JoinMatchHandler();
  ~JoinMatchHandler();

  void handle(Packet& packet, ClientManager& client_manager,
              MatchManager& match_manager) override;
};

#endif