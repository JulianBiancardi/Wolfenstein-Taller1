#include "door_interaction_handler.h"

DoorInteractionHandler::DoorInteractionHandler() {}

DoorInteractionHandler::~DoorInteractionHandler() {}

void DoorInteractionHandler::handle(Packet& packet,
                                    ClientManager& client_manager,
                                    MatchManager& match_manager) {
  unsigned char type;
  unsigned int player_id;
  unsigned char match_id;
  unpack(packet.get_data(), "CIC", &type, &player_id, &match_id);

  Match& match = match_manager.get_match(match_id);

  std::shared_ptr<Door> door_opened = match.open_door(player_id);
  if (door_opened != nullptr) {
    const std::unordered_set<unsigned int>& clients = match.get_players_ids();

    unsigned char data[DOOR_UPDATE_SIZE];
    size_t size =
        pack(data, "CICIIC", DOOR_UPDATE, player_id, match_id,
             (int)door_opened->get_position().getX(),
             (int)door_opened->get_position().getY(), door_opened->is_open());
    Packet door_update_packet(size, data);
    client_manager.send_to_all(clients, door_update_packet);
  }
}
