#include "match.h"

#include "../game/objects/door/door.h"

/*

#include "../events/event_building.h"


Match::Match(Map& map) : map(map), keep_running(true) {}

Match::~Match() {}

void Match::add_player(double initial_angle) {
  Player new_player(map.next_spawn_point(), initial_angle);
  players.insert({new_player.get_id(), new_player});
  result_events.emplace(std::piecewise_construct,
                        std::forward_as_tuple(new_player.get_id()),
                        std::forward_as_tuple());  // In-place construction
}

void Match::enqueue_event(const packet_t& event) {
  events_to_process.enqueue(event);
}

const packet_t Match::dequeue_result(int for_whom) {
  return result_events.at(for_whom)
      .dequeue();  // Throws out_of_range if not found
}

void Match::start() {
  keep_running = true;  // TODO Remove (Fix tests)
  EventHandlerBuilder builder;
  CollisionChecker checker(map, players, map.get_items(), map.get_objects());

  while (keep_running) {
    const packet_t next_event = events_to_process.dequeue();
    EventHandler* handler = builder.build(next_event, players);
    handler->handle(*this, checker);
    delete handler;

    if (events_to_process.is_empty())  // TODO Change way of ending loop
      keep_running = false;
  }
}

void Match::enqueue_result(const packet_t& event, int for_whom) {
  result_events.at(for_whom).enqueue(
      event);  // Throws out_of_range if not found
}

void Match::enqueue_result_for_all(const packet_t& event) {
  for (auto& queue : result_events) queue.second.enqueue(event);
}

void Match::enqueue_result_for_all_others(const packet_t& event,
                                          int others_than) {
  for (auto& queue : result_events) {
    if (queue.first != others_than) queue.second.enqueue(event);
  }
}

Map& Match::get_map() { return map; }

Player& Match::get_player(int id) { return players.at(id); }

bool Match::has_result_events_left(int id) {
  return !result_events.at(id).is_empty();
}

void Match::eliminate_player(int id) {
  players.erase(id);
  result_events.erase(id);  // TODO CHECK THIS! Should problably enqueue kill
                            // socket event to notify thread

  if (players.size() == 1) events_to_process.enqueue(build_game_over_packet());
}

void Match::end() { keep_running = false; }

*/

#include "match_error.h"

Match::Match(std::string& map_name) : map(map_name), checker(map) {}

Match::~Match() {}

bool Match::add_player(unsigned int player_id) {
  if (map.add_player(player_id)) {
    players_ids.insert(player_id);
    return true;
  } else {
    return false;
  }
}

bool Match::player_exists(unsigned int player_id) {
  return players_ids.find(player_id) != players_ids.end();
}

const std::unordered_set<unsigned int>& Match::get_players_ids() const {
  return players_ids;
}

const std::unordered_map<unsigned int, Player>& Match::get_players() const {
  return map.get_players();
}

unsigned char Match::get_id() const { return match_id; }

const std::string& Match::get_map_name() const { return map.get_name(); }

unsigned char Match::get_capacity() const { return map.get_capacity(); }

bool Match::has_started() const { return started; }

bool Match::move_player(unsigned int player_id, unsigned char direction) {
  if (!player_exists(player_id)) {
    throw MatchError("Failed to move player. Player %u doesn't exist.",
                     player_id);
  }

  Player& player = map.get_player(player_id);
  Point requested_position = player.next_position(direction);

  if (checker.can_move(requested_position, player)) {
    player.set_position(requested_position);

    return true;
  }
  return false;
}

bool Match::rotate_player(unsigned int player_id, unsigned char direction) {
  if (!player_exists(player_id)) {
    throw MatchError("Failed to rotate player. Player %u doesn't exist.",
                     player_id);
  }

  map.get_player(player_id).rotate(direction);

  return true;
}

unsigned int Match::grab_item(unsigned int player_id) {
  if (!player_exists(player_id)) {
    throw MatchError("Failed to grab item. Player %u doesn't exist.",
                     player_id);
  }

  Player& player = map.get_player(player_id);
  unsigned int item_id = checker.grabbed_item(player);

  if (item_id != 0) {
    Item& item = map.get_item(item_id);

    if (item.can_be_used_by(player)) {
      item.use(player);
      map.delete_item(item_id);
    }
  }

  return item_id;
}

bool Match::change_gun(unsigned int player_id, unsigned char gun_id) {
  if (!player_exists(player_id)) {
    throw MatchError("Failed to change gun player. Player %u doesn't exist.",
                     player_id);
  }

  // TODO Check if he has enough bullets to wield it
  return map.get_player(player_id).change_gun(gun_id);
}

bool Match::shoot_gun(unsigned int player_id, unsigned int objective_id,
                      unsigned char damage) {
  if (!player_exists(player_id)) {
    throw MatchError("Failed to shoot gun. Player %u doesn't exist.",
                     player_id);
  }

  if (objective_id != 0 && !player_exists(objective_id)) {
    throw MatchError("Failed to shoot at player. Player %u doesn't exist.",
                     objective_id);
  }

  Player& shooter = map.get_player(player_id);
  shooter.shoot();

  if (objective_id != 0) {
    Player& objective = map.get_player(objective_id);

    if (objective.is_dead()) {
      throw MatchError("Failed to shoot player. Player %u is dead.",
                       objective_id);
    }

    objective.receive_damage(damage);

    if (objective.is_dead()) {
      kill_player(objective_id);
      shooter.add_kill();
      map.add_drop(objective);

      return true;
    }
  }

  return false;
}

bool Match::is_dead(unsigned int player_id) {
  if (!player_exists(player_id)) {
    throw MatchError(
        "Failed to check health status. Player %u doesn't exist, he is neither "
        "alive nor dead.",
        player_id);
  }

  return map.get_player(player_id).is_dead();
}

void Match::kill_player(unsigned int player_id) {
  if (!player_exists(player_id)) {
    throw MatchError("Failed to kill player. Player %u doesn't exist.",
                     player_id);
  }

  Player& player = map.get_player(player_id);

  if (player.has_lives()) {
    player.respawn();
  } else {
    delete_player(player_id);
  }
}

bool Match::has_lives(unsigned int player_id) {
  if (!player_exists(player_id)) {
    throw MatchError("Failed to check lives. Player %u doesn't exist.",
                     player_id);
  }

  return map.get_player(player_id).has_lives();
}

bool Match::interact_with_door(unsigned int player_id, unsigned int door_id) {
  if (!player_exists(player_id)) {
    throw MatchError("Failed to find door interactor. Player %u doesn't exist.",
                     player_id);
  }

  Player& player = map.get_player(player_id);

  Door* door = (Door*)map.get_object(door_id);

  // FIXME
  if (door == nullptr) {
    throw MatchError("Failed to get door. Door %u doesn't exist.", door_id);
  }

  return door->interact(player, checker);
}

void Match::delete_player(unsigned int player_id) {  // TODO
  if (!player_exists(player_id)) {
    throw MatchError("Failed to delete player. Player %u doesn't exist.",
                     player_id);
  }
}

bool Match::should_end() const { return map.has_one_player(); }

void Match::end() {
  // TODO
}
