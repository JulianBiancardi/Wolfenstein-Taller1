#include "game_over_handler.h"

#include "../../../../../common/src/main/packets/packing.h"

GameOverHandler::GameOverHandler() = default;

GameOverHandler::~GameOverHandler() = default;

bool GameOverHandler::handle(Packet& packet, Map& map, GameSound& sound) {
  unsigned char type;
  unpack(packet.get_data(), "C", &type);

  return false;
}
