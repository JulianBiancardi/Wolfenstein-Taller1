#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_MATCH_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_MATCH_H_

#include <unordered_map>

#include "../../../../common/src/main/event_queue.h"
#include "../events/event_handler_builder.h"
#include "../map.h"
#include "collision_checker.h"
#include "../../../../common/src/main/object.h"
#include "player.h"

class Match {
 private:
  Map& map;
  std::unordered_map<int, int> test;
  std::unordered_map<int, Player> players;
  int players_id_count;
  EventQueue<packet_t> events_to_process;
  std::unordered_map<int, EventQueue<packet_t>> result_events; // <id, Queue>

 public:
  Match(Map& map);
  ~Match();

  void add_player(Point where, double initial_angle);  // Revise parameters, map
  void enqueue_event(const packet_t& event);              // has spawn points
  const packet_t dequeue_result(int for_whom);
  void start();

  Map& get_map();
  // Enqueuing results
  void enqueue_result(const packet_t& event, int for_whom);
  void enqueue_result_for_all(const packet_t& event);
  void enqueue_result_for_all_others(const packet_t& event, int others_than);
  Player& get_player(int id);  // Only used for testing
  bool has_result_events_left(int id); // Only used for testing
};

#endif  // WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_MATCH_H_
