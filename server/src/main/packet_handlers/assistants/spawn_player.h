#ifndef SPAWN_PLAYER_ASSISTANT_H
#define SPAWN_PLAYER_ASSISTANT_H

#include "../../../../../common/src/main/packets/packet.h"
#include "../../managers/client_manager.h"
#include "../../managers/match.h"
#include "assistant.h"

class SpawnPlayerAssistant : public PacketHandlerAssistant {
 private:
 public:
  SpawnPlayerAssistant();
  ~SpawnPlayerAssistant();

  Packet build_packet(unsigned int player_id, unsigned char player_gun,
                      Match& match) override;

};

#endif