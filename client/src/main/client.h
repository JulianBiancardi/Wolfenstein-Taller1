#ifndef CLIENT_H
#define CLIENT_H

#include <blocking_queue.h>
#include <protected_queue.h>
#include <receive_from_server_thread.h>
#include <send_to_server_thread.h>
#include <socket.h>

#include <string>

#include "../../../common/src/main/utils/ray.h"
#include "caster.h"
#include "events/event.h"
#include "map.h"
#include "sdl/window.h"

//-------------------------------------
class Client {
 private:
  Window window;
  Ray player_ray;
  Caster caster;
  Socket socket;
  BlockingQueue<packet_t>* events_queue;
  ProtectedQueue<packet_t>* reception_queue;
  SendToServerThread send_thread;
  ReceiveFromServerThread receive_thread;
  bool is_running;

  void handle_events();  // handle any user events
  void update();         // update all objects of the game
  void render();         // render thats changes
  void handle_key_press(SDL_Keycode& key);

 public:
  Client(std::string& host, std::string& port, Map& map);

  void launch();

  ~Client();
};

#endif  // CLIENT_H