#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_MATCH_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_MATCH_H_

#include <unordered_map>

#include "../../../../common/src/main/event_queue.h"
#include "../../../../common/src/main/object.h"
#include "../events/event_handler_builder.h"
#include "../map.h"
#include "collision_checker.h"
#include "player.h"

class Match2 {
 private:
  Map& map;
  std::unordered_map<int, int> test;
  std::unordered_map<int, Player> players;
  EventQueue<packet_t> events_to_process;
  std::unordered_map<int, EventQueue<packet_t>> result_events;  // <id, Queue>
  bool keep_running;

 public:
  Match2(Map& map);
  ~Match2();

  void add_player(double initial_angle);  // Could be spawn rays
  void enqueue_event(const packet_t& event);
  const packet_t dequeue_result(int for_whom);
  void start();

  Map& get_map();
  // Enqueuing results
  void enqueue_result(const packet_t& event, int for_whom);
  void enqueue_result_for_all(const packet_t& event);
  void enqueue_result_for_all_others(const packet_t& event, int others_than);
  Player& get_player(int id);           // Only used for testing
  bool has_result_events_left(int id);  // Only used for testing
  void eliminate_player(int id);
  void end();
};

class Match {
 private:
  std::vector<unsigned char> players_ids;
  std::unordered_map<unsigned char, Player> players;
  bool player_exists(unsigned char player_id);

 public:
  Match();
  ~Match();

  /* Returns a vector with all the ids of the players */
  std::vector<unsigned char>& get_players_ids();

  /* Move a player in the match */
  bool move_player(unsigned char player_id, unsigned char direction);

  /* Rotate a player in the given direction */
  bool rotate_player(unsigned char player_id, unsigned char direction);

  /* Change the gun of the player in the match */
  bool change_gun(unsigned char player_id, unsigned char gun_id);

  /* Shoot the gun of the player in the match */
  bool shoot_gun(unsigned char player_id, unsigned char objective_id,
                 unsigned char damage);

  /* Kill a player and respawn him */
  void kill_player(unsigned char player_id);

  /* Returns true if the player is dead, false otherwise */
  bool is_dead(unsigned char player_id);

  /* Returns true if the player has lives left */
  bool has_lives(unsigned char player_id);
};

Match::Match(/* args */) {}

Match::~Match() {}

#endif  // WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_MATCH_H_
