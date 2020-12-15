#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_MATCH_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_MATCH_H_

#include "../map.h"
#include "player.h"
#include "sprites/sprite.h"
#include "collision_checker.h"
#include "../../../../common/src/main/event_queue.h"
#include "../events/event_handler_builder.h"
#include <unordered_map>

class Match {
 private:
  Map &map;
  std::unordered_map<int, Player> players;
  std::vector<Sprite> sprites;
  EventQueue<Event> events_to_process;
  EventQueue<Event> result_events;
  int id_count;

  std::vector<std::reference_wrapper<Player>> get_players_as_vector();

 public:
  Match(Map &map);

  void add_player(Point where, double initial_angle);
  void enqueue_event(const Event &event);
  const Event dequeue_result();
  void start();

  void enqueue_result(const Event &event);
  int get_player_id(Player &player);
};

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_MATCH_H_
