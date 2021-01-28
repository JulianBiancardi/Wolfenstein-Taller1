#ifndef GAME_OVER_HANDLER_H
#define GAME_OVER_HANDLER_H

#include "packet_handler.h"

class GameOverHandler : public PacketHandler {
 private:
 public:
  GameOverHandler();
  ~GameOverHandler();

  void handle(Packet& packet, ClientManager& client_manager,
              MatchManager& match_manager) override;
};

#endif
