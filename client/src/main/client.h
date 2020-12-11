#ifndef CLIENT_H
#define CLIENT_H

#include "../../../common/src/main/utils/ray.h"
#include "caster.h"
#include "events/*.h"
#include "map.h"
#include "sdl/window.h"

//-------------------------------------
class Client {
 private:
  Window window;
  Ray player_ray;
  Caster caster;
  std::vector<Event> events;
  bool is_running;

  void handle_events();  // handle any user events
  void update();         // update all objects of the game
  void render();         // render thats changes

 public:
  explicit Client(Map& map);

  void launch();

  ~Client();
};

#endif  // CLIENT_H