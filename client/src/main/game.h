#ifndef GAME_H
#define GAME_H

#include <vector>

#include "../../../common/src/main/utils/ray.h"
#include "casters/game_caster.h"
#include "launcher/include/match.h"  // TODO Move smwhere else
#include "map.h"
#include "sdl/window.h"
#include "server.h"

#include "game_sound.h"

class Game {
 private:
  unsigned int player_id;
  unsigned char match_id;
  Server& server;
  Window window;
  Map map;
  GameCaster caster;
  GameSound gamesound;
  bool is_running;

  std::vector<bool> input_flags;

  /* Receive spawn point and add the player there. */
  void spawn_self();

  void update();  // update all objects of the game
  void render();  // render thats changes

  void handle_events();  // handle any user events
  void handle_key_press(SDL_Keycode& key);
  void handle_key_release(SDL_Keycode& key);
  void handle_click(SDL_MouseButtonEvent& button);
  void handle_unclick(SDL_MouseButtonEvent& button);

  void process_events();
  void process_movement();
  void process_rotation();
  void process_trigger();
  void process_match_start();

  void send_move_packet(unsigned char direction);

 public:
  Game(Server& server, Match& match);
  ~Game();

  void operator()();
};

#endif