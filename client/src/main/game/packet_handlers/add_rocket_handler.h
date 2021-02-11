#ifndef ADD_ROCKET_HANLDER_H
#define ADD_ROCKET_HANLDER_H

#include "../../../../../common/src/main/packets/packet.h"
#include "../audio/game_sound.h"
#include "../map/map.h"
#include "packet_handler.h"

class AddRocketHandler : public PacketHandler {
 private:
 public:
  AddRocketHandler();
  ~AddRocketHandler();

  void handle(Packet& packet, Map& map, GameSound& sound) override;
};

#endif
