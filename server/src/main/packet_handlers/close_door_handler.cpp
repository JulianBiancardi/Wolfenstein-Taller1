#include "close_door_handler.h"

#include "../../../../common/src/main/packets/packing.h"

CloseDoorHandler::CloseDoorHandler() {}

CloseDoorHandler::~CloseDoorHandler() {}

void CloseDoorHandler::handle(Packet& packet, ClientManager& client_manager,
                              MatchManager& match_manager) {
  unsigned char type;
  unsigned char match_id;
  unsigned int door_id;
  unpack(packet.get_data(), "CCI", &type, &match_id, &door_id);

  Match& match = match_manager.get_match(match_id);

  if (match.close_door(door_id)) {
    const std::unordered_set<unsigned int>& clients = match.get_players_ids();
    client_manager.send_to_all(clients, packet);
  }
}
