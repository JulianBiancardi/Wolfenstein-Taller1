#ifndef MATCH_H_
#define MATCH_H_

#include <unordered_map>

#include "../../../../common/src/main/data_structures/blocking_queue.h"
#include "../../../../common/src/main/packets/packet.h"
#include "../../../../common/src/main/threads/thread.h"
#include "../game/collisions/collision_checker.h"
#include "../game/objects/player.h"
#include "../game/map/map.h"

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
  bool start(unsigned int player_id, BlockingQueue<Packet>& queue);

  /* Create and add a new player to the match with the given id.
   * Returns true on success, false otherwise
   */
  bool add_player(unsigned int player_id);

  /* Creates and adds a new bot to the match with the given id.
   * Returns true on success, false otherwise
   */
  bool add_bot(unsigned int player_id);

  /* Returns true if the player is in the match, false otherwise */
  bool player_exists(unsigned int player_id);

  /* Returns a vector with all the ids of the players */
  const std::unordered_set<unsigned int>& get_players_ids() const;

  /* Returns a reference to the players */
  const std::unordered_map<unsigned int, Player>& get_players() const;

  /* Returns a reference to the items */
  const std::unordered_map<unsigned int, Item*>& get_items() const;

  /* Returns the match_id */
  unsigned char get_id() const;

  /* Returns the name of the map */
  const std::string& get_map_name() const;

  /* Returns the maximum amount of players allowed */
  unsigned char get_capacity() const;

  /* Returns the current status of the match */
  bool has_started() const;

  /* Move a player in the match.
   * Returns true on sucess, false otherwise.
   */
  bool move_player(unsigned int player_id, unsigned char direction);

  /* Rotate a player in the given direction.
   * Returns true on success, false otherwise.
   */
  bool rotate_player(unsigned int player_id, unsigned char direction);

  /* Returns the grabbed item id, otherwise returns 0 */
  unsigned int grab_item(unsigned int player_id);

  /* Change the gun of the player in the match.
   * Returns true on success, false otherwise.
   */
  bool change_gun(unsigned int player_id, unsigned char gun_id);

  /* Damages the player, kills if health is less or equal to 0 */
  void damage_player(unsigned int player_id, unsigned int damager_id,
                     unsigned char damage);

  /* Shoots player's gun and damages objective */
  void shoot_gun(unsigned int player_id, unsigned int objective_id,
                 unsigned char damage);

  /* Returns if the player is using a rocket launcher */
  bool is_using_rocket_launcher(unsigned int player_id);

  /* Adds rocket from player's position */
  void shoot_rocket(unsigned int player_id);

  /* Returns if the rocket can be moved */
  bool move_rocket(unsigned int rocket_id);

  /* Explodes the rocket and returns players damage and the damage made */
  std::map<unsigned int, unsigned char> explode_rocket(
      unsigned int rocket_id, unsigned int owner_id);

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
};

#endif
