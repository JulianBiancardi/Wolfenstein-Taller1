#include "match.h"

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

bool Match::player_exists(unsigned char player_id) {
  return players.find(player_id) != players.end();
}

/* Move a player in the match */
bool Match::move_player(unsigned char player_id, unsigned char direction) {
  if (!player_exists(player_id)) {
    throw 1;  // TODO Throw Error
  }

  Player& player = players[player_id];
  Point requested_position = player.next_position(direction);

  if (checker.can_move(requested_position, player)) {
    player.set_position(requested_position);
    // TODO Check if grabbed

    // match.enqueue_result_for_all(build_move_packet(who.get_id(), direction));
    // consequence_grab_event(match, checker, who);

    return true;
  }
  return false;
}

/* Rotate a player in the given direction */
bool Match::rotate_player(unsigned char player_id, unsigned char direction) {
  if (!player_exists(player_id)) {
    throw 1;  // TODO Throw Eerror
  }

  players[player_id].rotate(direction);

  return true;
}

/* Change the gun of the player in the match */
bool Match::change_gun(unsigned char player_id, unsigned char gun_id) {
  if (!player_exists(player_id)) {
    throw 1;  // TODO Throw error
  }

  // Check if he has enough bullets to wield it
  return players[player_id].change_gun(gun_id);
}

/* Shoot the gun of the player in the match */
bool Match::shoot_gun(unsigned char player_id, unsigned char objective_id,
                      unsigned char damage) {
  if (!player_exists(player_id)) {
    throw 1;  // TODO Throw error
  }

  if (objective_id != 0 && !player_exists(objective_id)) {
    throw 1;  // TODO THrow error. I separated them so we can say the id in
              // the error
  }

  Player& shooter = players[player_id];
  shooter.shoot();

  if (objective_id != 0) {
    Player& objective = players[objective_id];
    objective.receive_damage(damage);

    if (objective.is_dead()) {
      kill_player(objective_id);
      shooter.add_kill();
    }
  }
}

bool Match::is_dead(unsigned char player_id) {
  if (!player_exists(player_id)) {
    throw 1;  // TODO Throw error
  }

  return players[player_id].is_dead();
}
