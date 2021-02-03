#include "game.h"

#include "frame_limiter.h"

#define UNIT 5
#define SCREEN_WIDTH (320 * UNIT)
#define SCREEN_HEIGHT (200 * UNIT)

Game::Game(Server& server, Match& match)
    : server(server),
      window("Hello World!", SCREEN_WIDTH, SCREEN_HEIGHT),
      map("test_map"),
      player_ray(2.5, 2.5, 0),
      caster(window, player_ray, map),
      is_running(false) {}

Game::~Game() {}

void Game::operator()() {
  FrameLimiter frame_limiter;

  is_running = true;
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

void Game::handle_events() {
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
        player_ray = Ray(x + 0.1, y, angle);
        // player_ray.set_origin(x + 0.1, y);
        // TODO DELETE, ONLY TEST W Key
        // events_queue->enqueue(build_move_event(1, Point(x + 0.1, y)));
      } else if (cos_angle < -0.9) {
        player_ray = Ray(x - 0.1, y, angle);
        // player_ray.set_origin(x - 0.1, y);
        // events_queue->enqueue(build_move_event(1, Point(x - 0.1, y)));
      } else if (sin_angle > 0.9) {
        player_ray = Ray(x, y - 0.1, angle);
        // events_queue->enqueue(build_move_event(1, Point(x, y - 0.1)));
      } else if (sin_angle < -0.9) {
        player_ray = Ray(x, y + 0.1, angle);
        // events_queue->enqueue(build_move_event(1, Point(x, y + 0.1)));
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
      player_ray = Ray(x, y, angle);
      break;
    case SDLK_d:
      angle -= 0.1;
      if (angle < 0) {
        angle += 2 * M_PI;
      }
      // player_ray.set_angle(angle);
      player_ray = Ray(x, y, angle);
      break;
    default:
      break;
  }
}

void Game::update() {
  BlockingQueue<Packet>& reception_queue = server.get_reception_queue();
  Packet packet;
  while (reception_queue.poll(packet)) {
  }
}

void Game::render() { caster(); }