#include "client.h"

#include "frame_limiter.h"

#define UNIT 5
#define SCREEN_WIDTH (320 * UNIT)
#define SCREEN_HEIGHT (200 * UNIT)

//------------------------------------------------
Client::Client(Map& map)
    : window("Hello World!", SCREEN_WIDTH, SCREEN_HEIGHT),
      player_ray(1.5, 1.5, 0),
      caster(window, player_ray, map),
      is_running(true) {}

void Client::launch() {
  FrameLimiter frame_limiter;

  while (is_running) {
    handle_events();  // handle any user events
    update();         // update all objects of the game
    render();         // render thats changes

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
      // handle_key_press(event.key.keysym.sym, player);
      // caster();
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

void Client::update() {
  // Pensar en tener un update por cada objecto que necesite ser actualizado y
  // llamar a esos metodos, en vez de actualizar todo aca
}

void Client::render() {  // this->caster();
}

Client::~Client() {}