#include "packet_handler_factory.h"

#include "../../../../common/src/main/packets/packet_error.h"
#include "../../../../common/src/main/packets/packet_handler_factory_error.h"
#include "join_match_handler.h"
#include "request_matches_handler.h"
#include "request_new_match_handler.h"
#include "move_handler.h"
#include "rotation_handler.h"
#include "shot_handler.h"
#include "change_gun_handler.h"
#include "door_interaction_handler.h"
#include "close_door_handler.h"
#include "game_over_handler.h"

PacketHandler* PacketHandlerFactory::build(Packet& packet) {
  switch (packet.get_type()) {
    case REQUEST_MATCHES: return new RequestMatchesHandler();
    case REQUEST_NEW_MATCH: return new RequestNewMatchHandler();
    case JOIN_MATCH: return new JoinMatchHandler();
    case MOVE: return new MoveHandler();
    case ROTATE: return new RotationHandler();
    case SHOT: return new ShotHandler();
    case CHANGE_GUN: return new ChangeGunHandler();
    case DOOR_INTERACTION: return new DoorInteractionHandler();
    case CLOSE_DOOR: return new CloseDoorHandler();
    case GAME_OVER: return new GameOverHandler();
    default:
      throw PacketHandlerFactoryError("Packet type is not valid. Type is %u.",
                                      packet.get_type());
  }
}