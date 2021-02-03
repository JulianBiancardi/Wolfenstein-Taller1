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
  Server& server;
  Window window;
  Map map;
  Ray player_ray;
  GameCaster caster;
  bool is_running;

  void update();  // update all objects of the game
  void render();  // render thats changes

  void handle_events();  // handle any user events
  void handle_key_press(SDL_Keycode& key);
  /*Ray player_ray;
  Socket socket;
  BlockingQueue<packet_t>* events_queue;
  ProtectedQueue<packet_t>* reception_queue;
  SendToServerThread send_thread;
  ReceiveFromServerThread receive_thread;
  bool is_running;


  */

 public:
  Game(Server& server, Match& match);
  ~Game();

  void operator()();
};

#endif