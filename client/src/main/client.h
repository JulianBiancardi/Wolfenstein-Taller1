#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include "../../../common/src/main/data_structures/blocking_queue.h"
#include "../../../common/src/main/socket/socket.h"
#include "../../../common/src/main/utils/ray.h"

//-------------------------------------
/*
class Client2 {
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
  Client(std::string& host, std::string& port);

  void launch();

  ~Client();
}; */

class Client {
 private:
 public:
  Client();
  ~Client();

  void run_client(int argc, char** argv);
};

#endif  // CLIENT_H