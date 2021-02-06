#ifndef MATCH_H_
#define MATCH_H_

#include <unordered_map>

#include "../../../../common/src/main/data_structures/blocking_queue.h"
#include "../../../../common/src/main/packets/packet.h"
#include "../../../../common/src/main/threads/thread.h"
#include "../game/collision_checker.h"
#include "../game/player.h"
#include "../map.h"

class Match {
 private:
  unsigned int host_id;
  unsigned char match_id;
  bool started;
  std::unordered_set<unsigned int> players_ids;
  Map map;
  CollisionChecker checker;
  std::map<int, Thread*> threads;

 public:
  explicit Match(unsigned int host_id, unsigned char match_id,
                 std::string& map_name);

  Match(const Match& other) = delete;
  Match& operator=(const Match&) = delete;

  Match(Match&& other) = delete;
  Match& operator=(Match&& other) = delete;

  ~Match();

  /* Starts the match given the host id.
   * Returns true on success, false otherwise.
   */
  bool start(unsigned int player_id);

  /* Create and add a new player to the match with the given id.
   * Returns true on success, false otherwise
   */
  bool add_player(unsigned int player_id);

  /* Returns true if the player is in the match, false otherwise */
  bool player_exists(unsigned int player_id);

  /* Returns a vector with all the ids of the players */
  const std::unordered_set<unsigned int>& get_players_ids() const;

  /* Returns a reference to the players */
  const std::unordered_map<unsigned int, Player>& get_players() const;

  /* Returns the match_id */
  unsigned char get_id() const;

  /* Returns the name of the map */
  const std::string& get_map_name() const;

  /* Returns the maximum amount of players allowed */
  unsigned char get_capacity() const;

  /* Returns the current status of the match */
  bool has_started() const;

  /* Move a player in the match */
  bool move_player(unsigned int player_id, unsigned char direction);

  /* Rotate a player in the given direction */
  bool rotate_player(unsigned int player_id, unsigned char direction);

  /* Returns the grabbed item id, otherwise returns 0 */
  unsigned int grab_item(unsigned int player_id);

  /* Change the gun of the player in the match */
  bool change_gun(unsigned int player_id, unsigned char gun_id);

  /* Shoot the gun of the player in the match, returns if objective is killed */
  bool shoot_gun(unsigned int player_id, unsigned int objective_id,
                 unsigned char damage);

  /* Kill a player and respawn him */
  void kill_player(unsigned int player_id);

  /* Returns true if the player is dead, false otherwise */
  bool is_dead(unsigned int player_id);

  /* Returns true if the player has lives left */
  bool has_lives(unsigned int player_id);

  /* Returns if the door state changes */
  bool interact_with_door(unsigned int player_id, unsigned int door_id);

  /* Closes the door, returns if could do it */
  bool close_door(unsigned int door_id);

  /* Delete player from the match */
  void delete_player(unsigned int player_id);

  /* Returns if match should end (does not check time) */
  bool should_end() const;

  /* Ends match */
  void end();
};

#endif
