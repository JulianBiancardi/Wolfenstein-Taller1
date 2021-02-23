#include "packet_handler_factory.h"

#include "../../../../../common/src/main/packets/packet.h"
#include "../../../../../common/src/main/packets/packet_handler_factory_error.h"
#include "add_rocket_handler.h"
#include "change_gun_handler.h"
#include "door_update_handler.h"
#include "explode_rocket_handler.h"
#include "game_over_handler.h"
#include "grab_handler.h"
#include "move_rocket_handler.h"
#include "movement_handler.h"
#include "rotation_handler.h"
#include "shot_handler.h"
#include "spawn_player_handler.h"

PacketHandler* PacketHandlerFactory::build(Packet& packet) {
  switch (packet.get_type()) {
    case MOVEMENT:
      return new MovementHandler();
    case ROTATION:
      return new RotationHandler();
    case SHOT:
      return new ShotHandler();
    case CHANGE_GUN:
      return new ChangeGunHandler();
    case GRAB:
      return new GrabHandler();
    case SPAWN_PLAYER:
      return new SpawnPlayerHandler();
    case ROCKET_ADD:
      return new AddRocketHandler();
    case ROCKET_MOVE:
      return new MoveRocketHandler();
    case ROCKET_EXPLODE:
      return new ExplodeRocketHandler();
    case GAME_OVER:
      return new GameOverHandler();
    case DOOR_UPDATE:
      return new DoorUpdateHandler();
    default:
      throw PacketHandlerFactoryError("Packet type is not valid. Type is %u.",
                                      packet.get_type());
      break;
  }
}