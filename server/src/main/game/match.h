#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_MATCH_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_MATCH_H_

#include <unordered_map>

#include "../../../../common/src/main/event_queue.h"
#include "../events/event_handler_builder.h"
#include "../map.h"
#include "collision_checker.h"
#include "objects/object.h"
#include "player.h"

class Match {
 private:
  Map& map;
  std::unordered_map<int, int> test;
  std::unordered_map<int, Player> players;
  int players_id_count;
  EventQueue<Event> events_to_process;
  EventQueue<Event> result_events;

 public:
  Match(Map& map);
  ~Match();

  void add_player(Point where, double initial_angle);  // Revise parameters, map
  void enqueue_event(const Event& event);              // has spawn points
  const Event dequeue_result();
  void start();

  Map& get_map();
  void enqueue_result(const Event& event);
  Player& get_player(int id);  // Only used for testing
};

#endif  // WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_MATCH_H_
