#ifndef GAME_H
#define GAME_H

#include "../launcher/include/match.h"     // TODO Move match smwhere else
#include "../launcher/include/settings.h"  // TODO Move settings smwhere else
#include "../server.h"
#include "audio/game_sound.h"
#include "map/map.h"
#include "rendering/game_caster.h"
#include "rendering/sdl/window.h"

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

  std::vector<unsigned int> input_flags;

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
  void process_gun_changes();
  void process_key_uses();
  void process_match_start();

  void send_move_packet(unsigned char direction);

 public:
  Game(Server& server, const Settings& settings, Match& match);
  ~Game();

  void operator()();
};

#endif