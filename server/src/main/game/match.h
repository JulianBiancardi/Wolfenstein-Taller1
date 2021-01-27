#ifndef MATCH_H_
#define MATCH_H_

#include <unordered_map>

#include "../map.h"
#include "collision_checker.h"
#include "player.h"

/*
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
}; */

class Match {
 private:
  unsigned char match_id;
  bool started;
  Map map;
  std::vector<unsigned int> players_ids;
  std::unordered_map<unsigned int, Player> players;
  CollisionChecker checker;

 public:
  Match();
  ~Match();

  /* Returns true if the player is in the match, false otherwise */
  bool player_exists(unsigned int player_id);

  /* Returns a vector with all the ids of the players */
  const std::vector<unsigned int>& get_players_ids() const;

  /* Returns a reference to the players */
  const std::unordered_map<unsigned int, Player>& get_players() const;

  /* Returns the match_id */
  unsigned char get_id() const;

  /* Returns the name of the map */
  const char* get_map_name() const;

  /* Returns the maximum amount of players allowed */
  unsigned char get_capacity() const;

  /* Returns the current status of the match */
  bool has_started() const;

  /* Move a player in the match */
  bool move_player(unsigned int player_id, unsigned char direction);

  /* Rotate a player in the given direction */
  bool rotate_player(unsigned int player_id, unsigned char direction);

  /* Change the gun of the player in the match */
  bool change_gun(unsigned int player_id, unsigned char gun_id);

  /* Shoot the gun of the player in the match */
  void shoot_gun(unsigned int player_id, unsigned int objective_id,
                 unsigned char damage);

  /* Kill a player and respawn him */
  void kill_player(unsigned int player_id);

  /* Returns true if the player is dead, false otherwise */
  bool is_dead(unsigned int player_id);

  /* Returns true if the player has lives left */
  bool has_lives(unsigned int player_id);
};

#endif
