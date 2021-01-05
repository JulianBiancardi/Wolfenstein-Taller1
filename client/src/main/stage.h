#ifndef WOLFENSTEIN_TALLER1_CLIENT_SRC_MAIN_STAGE_H_
#define WOLFENSTEIN_TALLER1_CLIENT_SRC_MAIN_STAGE_H_

#include <unordered_map>
#include "player.h"
//#include "events/event.h"
#include "../../../../common/src/main/event_queue.h"

// TODO Move to common space
typedef struct PointData {
  double x;
  double y;
} PointData;

class Stage {
 private:
  //EventQueue<std::unique_ptr<Event>> &events;
  //EventQueue<Event> events;
  Map map;
  int my_id_player;
  int health;
  std::unordered_map<int, Player> players;
 public:
  Stage(/*EventQueue<std::unique_ptr<Event>> &queue*/);
  void setPlayerPosition(int id, PointData point_data);
  void setPlayerHealth(int id, int health);
  void addItem(int type, PointData point_data);
  void removeItem(PointData point_data);
  void removePlayer(int id);
};

#endif //WOLFENSTEIN_TALLER1_CLIENT_SRC_MAIN_STAGE_H_
