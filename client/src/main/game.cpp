#include "game.h"

#include <syslog.h>

#include <cmath>
#include <memory>

#include "../../../common/src/main/ids/movement_ids.h"
#include "../../../common/src/main/packets/packet.h"
#include "../../../common/src/main/packets/packet_error.h"
#include "../../../common/src/main/packets/packet_handler_factory_error.h"
#include "../../../common/src/main/packets/packing.h"
#include "frame_limiter.h"
#include "packet_handlers/packet_handler_factory.h"

#define UNIT 3
#define SCREEN_WIDTH (320 * UNIT)
#define SCREEN_HEIGHT (200 * UNIT)

#define FLAGS 7
#define FORWARD_FLAG 0
#define LEFT_FLAG 1
#define BACKWARD_FLAG 2
#define RIGHT_FLAG 3
#define ROTATE_LEFT_FLAG 4
#define ROTATE_RIGHT_FLAG 5
#define ENTER_FLAG 6

Game::Game(Server& server, Match& match)
    : player_id(server.get_id()),
      match_id(match.get_match_id()),
      server(server),
      window("Hello World!", SCREEN_WIDTH, SCREEN_HEIGHT),
      map("test_map"),
      caster(window, map, player_id),
      is_running(false),
      input_flags(FLAGS, false),
      gamesound(GameSound(Point(map.get_rows(), map.get_columns()))){}

Game::~Game() {}

void Game::operator()() {
  FrameLimiter frame_limiter;

  is_running = true;

  spawn_self();

  gamesound.set_point(map.get_player(player_id).get_position());
  gamesound.play_background();
  while (is_running) {
    handle_events();
    process_events();
    update();
    render();
    frame_limiter.sleep();
    //gamesound.set_point(map.get_player(player_id).get_position());
    //Point punto(0,0);
    //gamesound.play_shoot(punto);
  }
}

void Game::spawn_self() {
  BlockingQueue<Packet>& reception_queue = server.get_reception_queue();
  Packet packet;
  reception_queue.dequeue(packet);
  if (packet.get_type() != SPAWN_PLAYER) {
    throw PacketError("Failed to receive spawn packet upon match start.");
  }

  unsigned char type;
  unsigned int player_id;
  unsigned char x_pos;
  unsigned char y_pos;
  unpack(packet.get_data(), "CICC", &type, &player_id, &x_pos, &y_pos);

  map.add_player(player_id, Ray(x_pos + 0.5, y_pos + 0.5, 0));
}

void Game::handle_events() {
  // TODO Check how to move everything into a flags vector
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        this->is_running = false;
        break;
      case SDL_KEYDOWN:
        handle_key_press(event.key.keysym.sym);
        break;
      case SDL_KEYUP:
        handle_key_release(event.key.keysym.sym);
        break;
      case SDL_MOUSEBUTTONDOWN:
        break;
      case SDL_MOUSEBUTTONUP:
        break;
      default:
        break;
    }
  }
}

void Game::handle_key_press(SDL_Keycode& key) {
  switch (key) {
    case SDLK_w:
      input_flags[FORWARD_FLAG] = true;
      break;
    case SDLK_s:
      input_flags[BACKWARD_FLAG] = true;
      break;
    case SDLK_a:
      input_flags[LEFT_FLAG] = true;
      break;
    case SDLK_d:
      input_flags[RIGHT_FLAG] = true;
      break;
    case SDLK_e:
      input_flags[ROTATE_RIGHT_FLAG] = true;
      break;
    case SDLK_q:
      input_flags[ROTATE_LEFT_FLAG] = true;
      break;
    case SDLK_RETURN:  // Enter
      input_flags[ENTER_FLAG] = true;
      break;
    default:
      break;
  }
}

void Game::handle_key_release(SDL_Keycode& key) {
  switch (key) {
    case SDLK_w:
      input_flags[FORWARD_FLAG] = false;
      break;
    case SDLK_s:
      input_flags[BACKWARD_FLAG] = false;
      break;
    case SDLK_a:
      input_flags[LEFT_FLAG] = false;
      break;
    case SDLK_d:
      input_flags[RIGHT_FLAG] = false;
      break;
    case SDLK_e:
      input_flags[ROTATE_RIGHT_FLAG] = false;
      break;
    case SDLK_q:
      input_flags[ROTATE_LEFT_FLAG] = false;
      break;
    case SDLK_RETURN:
      input_flags[ENTER_FLAG] = false;
      break;
    default:
      break;
  }
}

void Game::process_events() {
  process_movement();
  process_rotation();
  process_match_start();
}

void Game::process_movement() {
  if (!input_flags[FORWARD_FLAG] && !input_flags[BACKWARD_FLAG] &&
      !input_flags[RIGHT_FLAG] && !input_flags[LEFT_FLAG]) {
    return;
  }

  // Check where to move, in the order of most common to least common
  unsigned char direction = INVALID_MOVEMENT;
  if (input_flags[FORWARD_FLAG] && !input_flags[BACKWARD_FLAG]) {
    if (!input_flags[LEFT_FLAG] && !input_flags[RIGHT_FLAG]) {
      direction = UP;
    } else if (input_flags[LEFT_FLAG] && !input_flags[RIGHT_FLAG]) {
      direction = UP_LEFT;
    } else if (!input_flags[LEFT_FLAG] && input_flags[RIGHT_FLAG]) {
      direction = UP_RIGHT;
    } else {
      direction = UP;
    }
  } else if (!input_flags[FORWARD_FLAG] && !input_flags[BACKWARD_FLAG]) {
    if (input_flags[LEFT_FLAG] && !input_flags[RIGHT_FLAG]) {
      direction = LEFT;
    } else if (!input_flags[LEFT_FLAG] && input_flags[RIGHT_FLAG]) {
      direction = RIGHT;
    }
  } else if (!input_flags[FORWARD_FLAG] && input_flags[BACKWARD_FLAG]) {
    if (!input_flags[LEFT_FLAG] && !input_flags[RIGHT_FLAG]) {
      direction = DOWN;
    } else if (input_flags[LEFT_FLAG] && !input_flags[RIGHT_FLAG]) {
      direction = DOWN_LEFT;
    } else if (!input_flags[LEFT_FLAG] && input_flags[RIGHT_FLAG]) {
      direction = DOWN_RIGHT;
    } else {
      direction = DOWN;
    }
  } else {
    if (input_flags[LEFT_FLAG] && !input_flags[RIGHT_FLAG]) {
      direction = LEFT;
    } else if (!input_flags[LEFT_FLAG] && input_flags[RIGHT_FLAG]) {
      direction = RIGHT;
    } else {
      return;
    }
  }

  unsigned char data[MOVEMENT_SIZE];
  size_t size = pack(data, "CICC", MOVEMENT, player_id, match_id, direction);
  Packet move_packet(size, data);
  server.send(move_packet);
}

void Game::process_rotation() {
  if (!input_flags[ROTATE_LEFT_FLAG] && !input_flags[ROTATE_RIGHT_FLAG]) {
    return;
  }

  unsigned char direction = INVALID_ROTATION;
  if (input_flags[ROTATE_LEFT_FLAG] && !input_flags[ROTATE_RIGHT_FLAG]) {
    direction = LEFT_ROTATION;
  } else if (!input_flags[ROTATE_LEFT_FLAG] && input_flags[ROTATE_RIGHT_FLAG]) {
    direction = RIGHT_ROTATION;
  } else {
    return;
  }

  unsigned char data[ROTATION_SIZE];
  size_t size = pack(data, "CICC", ROTATION, player_id, match_id, direction);
  Packet move_packet(size, data);
  server.send(move_packet);
}

void Game::process_match_start() {
  if (!input_flags[ENTER_FLAG]) {
    return;
  }

  unsigned char data[MATCH_START_SIZE];
  size_t size = pack(data, "CIC", MATCH_START, player_id, match_id);
  Packet match_start_packet(size, data);
  server.send(match_start_packet);
}

void Game::update() {
  BlockingQueue<Packet>& reception_queue = server.get_reception_queue();
  Packet packet;
  while (reception_queue.poll(packet)) {
    try {
      std::unique_ptr<PacketHandler> handler(
          PacketHandlerFactory::build(packet));
      handler->handle(packet, map);
    } catch (const PacketHandlerFactoryError& e) {
      syslog(LOG_ERR, "Packet received hasn't got a valid type.");
    }
  }
}

void Game::render() { caster(); }