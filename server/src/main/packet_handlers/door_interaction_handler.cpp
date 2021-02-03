#include "door_interaction_handler.h"

#include "../../../../common/src/main/packets/packing.h"

DoorInteractionHandler::DoorInteractionHandler() {}

DoorInteractionHandler::~DoorInteractionHandler() {}

void DoorInteractionHandler::handle(Packet& packet,
                                    ClientManager& client_manager,
                                    MatchManager& match_manager) {
  unsigned char type;
  unsigned int player_id;
  unsigned char match_id;
  unsigned int door_id;
  unpack(packet.get_data(), "CICI", &type, &player_id, &match_id, &door_id);

  Match& match = match_manager.get_match(match_id);

  if (match.interact_with_door(player_id, door_id)) {
    const std::unordered_set<unsigned int>& clients = match.get_players_ids();
    client_manager.send_to_all(clients, packet);
  }
}
