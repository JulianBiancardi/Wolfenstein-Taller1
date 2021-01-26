#include "client.h"

#include "../../../common/src/main/utils/point.h"  //TODO MOVE THIS TO OTHER CLASSES
#include "../../../server/src/main/events/event_building.h"
#include "frame_limiter.h"

#define UNIT 5
#define SCREEN_WIDTH (320 * UNIT)
#define SCREEN_HEIGHT (200 * UNIT)

/*
//------------------------------------------------
Client::Client(std::string& host, std::string& port)
    : window("Hello World!", SCREEN_WIDTH, SCREEN_HEIGHT),
      player_ray(1.5, 1.5, 0),
      caster(window, player_ray, map),
      socket(host, port),
      send_thread(socket, events_queue),
      receive_thread(socket, reception_queue),
      is_running(true) {
  events_queue = new BlockingQueue<packet_t>();
  reception_queue = new ProtectedQueue<packet_t>();
}

void Client::launch() {
  FrameLimiter frame_limiter;
  send_thread.run();
  receive_thread.run();

  // EventQueue<Event *> event_queue;
  // EventHandler event_handler;
  // event_handler.setCaster(Caster);

  while (is_running) {
    handle_events();

    // Receive events
    // MovementEvent movement_event;
    // movement_event.setCaster(caster);
    // movement_event.process();

    update();
    render();
    frame_limiter.sleep();
  }
}

void Client::handle_events() {
  SDL_Event event;
  SDL_PollEvent(&event);
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
void Client::handle_key_press(SDL_Keycode& key) {
  double angle = player_ray.get_angle();
  double cos_angle = cos(angle);
  double sin_angle = sin(angle);
  Point position = player_ray.get_origin();
  double x = position.getX();
  double y = position.getY();

// FIXME
switch (key) {
  case SDLK_w:
    if (cos_angle > 0.9) {
      // player_ray.set_origin(x + 0.1, y);
      // TODO DELETE, ONLY TEST W Key
      events_queue->enqueue(build_move_event(1, Point(x + 0.1, y)));

    } else if (cos_angle < -0.9) {
      // player_ray.set_origin(x - 0.1, y);
      events_queue->enqueue(build_move_event(1, Point(x - 0.1, y)));
    } else if (sin_angle > 0.9) {
      // player_ray.set_origin(x, y - 0.1);
      events_queue->enqueue(build_move_event(1, Point(x, y - 0.1)));
    } else if (sin_angle < -0.9) {
      // player_ray.set_origin(x, y + 0.1);
      events_queue->enqueue(build_move_event(1, Point(x, y + 0.1)));
    }
    break;
  case SDLK_s:
    break;
  case SDLK_a:
    angle += 0.1;
    if (angle >= 2 * M_PI) {
      angle -= 2 * M_PI;
    }
    // player_ray.set_angle(angle);
    break;
  case SDLK_d:
    angle -= 0.1;
    if (angle < 0) {
      angle += 2 * M_PI;
    }
    // player_ray.set_angle(angle);
    break;
  default:
    break;
}
}

void Client::update() {}

void Client::render() { caster(); }

Client::~Client() {
  delete events_queue;
  delete reception_queue;
}

*/

#include "../../../common/src/main/config_loader.h"
#include "game/launcher.h"
#include "sdl/window.h"
#include "server.h"

Client::Client()
    : window("Wolfenstein 3D", CL::screen_width, CL::screen_height) {}

Client::~Client() {}

void Client::run_client() {
  Server server;
  Launcher launcher(server, window);
  Match match_joined = launcher();
  // Lobby lobby(server, window, match_joined);
  // Game game(server, window, map);
}