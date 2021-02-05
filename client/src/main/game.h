#ifndef GAME_H
#define GAME_H

#include "../../../common/src/main/utils/ray.h"
#include "casters/game_caster.h"
#include "launcher/include/match.h"  // TODO Move smwhere else
#include "map.h"
#include "sdl/window.h"
#include "server.h"

class Game {
 private:
  unsigned int player_id;
  unsigned char match_id;
  Server& server;
  Window window;
  Map map;
  GameCaster caster;
  bool is_running;

  unsigned char forward_velocity;
  unsigned char sideways_velocity;
  unsigned char angular_velocity;

  void update();  // update all objects of the game
  void render();  // render thats changes

  void handle_events();  // handle any user events
  void handle_key_press(SDL_Keycode& key);
  void handle_key_release(SDL_Keycode& key);

  void process_events();
  void process_movement();
  void process_rotation();

  void send_move_packet(unsigned char direction);

 public:
  Game(Server& server, Match& match);
  ~Game();

  void operator()();
};

#endif