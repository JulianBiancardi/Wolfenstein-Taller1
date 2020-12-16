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
  std::unordered_map<int, Items *> items;
  std::vector<Sprite> sprites;
  EventQueue<Event> events_to_process;
  EventQueue<Event> result_events;
  int players_id_count;
  int items_id_count;

  std::vector<std::reference_wrapper<Player>> get_players_as_vector();
  std::vector<Items *> get_items_as_vector();

 public:
  Match(Map &map);
  ~Match();

  void add_player(Point where, double initial_angle);
  void add_item(Items *what); // TODO One method for each item
  void enqueue_event(const Event &event);
  const Event dequeue_result();
  void start();

  void enqueue_result(const Event &event);
  int get_player_id(Player &player); //TODO Remove
  int get_item_id(Items *item); //TODO Remove
  Player &get_player(int id); //Only used for testing
};

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_MATCH_H_
