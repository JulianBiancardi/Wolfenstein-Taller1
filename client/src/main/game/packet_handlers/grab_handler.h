#ifndef GRAB_HANDLER_H
#define GRAB_HANDLER_H

#include "../../../../../common/src/main/packets/packet.h"
#include "../audio/game_sound.h"
#include "../map/map.h"
#include "packet_handler.h"

class GrabHandler : public PacketHandler {
 private:
 public:
  GrabHandler();
  ~GrabHandler();

  void handle(Packet& packet, Map& map, GameSound& sound) override;
};

#endif