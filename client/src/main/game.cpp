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

Game::Game(Server& server, Match& match)
    : player_id(server.get_id()),
      match_id(match.get_match_id()),
      server(server),
      window("Hello World!", SCREEN_WIDTH, SCREEN_HEIGHT),
      map("test_map"),
      caster(window, map, player_id),
      is_running(false),
      forward_velocity(0),
      sideways_velocity(0),
      angular_velocity(0),
      match_start(0) {}

Game::~Game() {}

void Game::operator()() {
  FrameLimiter frame_limiter;

  is_running = true;

  spawn_self();

  while (is_running) {
    printf("A\n");
    handle_events();
    printf("B\n");
    process_events();
    printf("C\n");
    update();
    printf("D\n");
    render();
    printf("E\n");
    frame_limiter.sleep();
    printf("F\n");
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
        printf("Key press\n");
        handle_key_press(event.key.keysym.sym);
        break;
      case SDL_KEYUP:
        printf("Key release\n");
        handle_key_release(event.key.keysym.sym);
        break;
      case SDL_MOUSEBUTTONDOWN:
        printf("Mouse clicked\n");
        break;
      case SDL_MOUSEBUTTONUP:
        printf("Mouse unclicked\n");
        break;
      default:
        break;
    }
  }
}

void Game::handle_key_press(SDL_Keycode& key) {
  switch (key) {
    case SDLK_w:
      forward_velocity = std::min(1, forward_velocity + 1);
      break;
    case SDLK_s:
      forward_velocity = std::max(-1, forward_velocity - 1);
      break;
    case SDLK_a:
      sideways_velocity = std::max(-1, sideways_velocity - 1);
      break;
    case SDLK_d:
      sideways_velocity = std::min(1, sideways_velocity + 1);
      break;
    case SDLK_e:
      angular_velocity = std::max(-1, angular_velocity - 1);
      break;
    case SDLK_q:
      angular_velocity = std::min(1, angular_velocity + 1);
      break;
    case SDLK_RETURN:  // Enter
      match_start = 1;
      break;
    default:
      break;
  }
}

void Game::handle_key_release(SDL_Keycode& key) {
  switch (key) {
    case SDLK_w:
      forward_velocity = std::min(0, forward_velocity - 1);
      break;
    case SDLK_s:
      forward_velocity = std::max(0, forward_velocity + 1);
      break;
    case SDLK_a:
      sideways_velocity = std::max(0, sideways_velocity + 1);
      break;
    case SDLK_d:
      sideways_velocity = std::min(0, sideways_velocity - 1);
      break;
    case SDLK_e:
      angular_velocity = std::max(0, angular_velocity + 1);
      break;
    case SDLK_q:
      angular_velocity = std::min(0, angular_velocity - 1);
      break;
    case SDLK_RETURN:
      match_start = 0;
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
  if (forward_velocity == 0 && sideways_velocity == 0) {
    return;
  }

  unsigned char direction = INVALID_MOVEMENT;
  if (forward_velocity == 1) {
    if (sideways_velocity == 0) {
      direction = UP;
    } else if (sideways_velocity == -1) {
      direction = UP_LEFT;
    } else if (sideways_velocity == 1) {
      direction = UP_RIGHT;
    }
  } else if (forward_velocity == 0) {
    if (sideways_velocity == -1) {
      direction = LEFT;
    } else if (sideways_velocity == 1) {
      direction = RIGHT;
    }
  } else if (forward_velocity == -1) {
    if (sideways_velocity == 0) {
      direction = DOWN;
    } else if (sideways_velocity == -1) {
      direction = DOWN_LEFT;
    } else if (sideways_velocity == 1) {
      direction = DOWN_RIGHT;
    }
  }

  unsigned char data[MOVEMENT_SIZE];
  size_t size = pack(data, "CICC", MOVEMENT, player_id, match_id, direction);
  Packet move_packet(size, data);
  server.send(move_packet);
}

void Game::process_rotation() {
  if (angular_velocity == 0) {
    return;
  }

  unsigned char direction = INVALID_ROTATION;
  if (angular_velocity == -1) {
    direction = RIGHT_ROTATION;
  } else if (angular_velocity == 1) {
    direction = LEFT_ROTATION;
  }

  unsigned char data[ROTATION_SIZE];
  size_t size = pack(data, "CICC", ROTATION, player_id, match_id, direction);
  Packet move_packet(size, data);
  server.send(move_packet);
}

void Game::process_match_start() {
  if (match_start == 0) {
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