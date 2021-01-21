#include "match.h"
#include "../events/event_building.h"

Match::Match(Map& map) : map(map), keep_running(true) {}

Match::~Match() {}

void Match::add_player(double initial_angle) {
  Player new_player(map.next_spawn_point(), initial_angle);
  players.insert({new_player.get_id(), new_player});
  result_events.emplace(std::piecewise_construct,
                        std::forward_as_tuple(new_player.get_id()),
                        std::forward_as_tuple()); // In-place construction
}

void Match::enqueue_event(const packet_t& event) {
  events_to_process.enqueue(event);
}

const packet_t Match::dequeue_result(int for_whom) {
  return result_events.at(for_whom).dequeue(); // Throws out_of_range if not found
}

void Match::start() {
  keep_running = true; // TODO Remove (Fix tests)
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
  result_events.at(for_whom).enqueue(event); // Throws out_of_range if not found
}

void Match::enqueue_result_for_all(const packet_t& event) {
  for (auto& queue : result_events)
    queue.second.enqueue(event);
}

void Match::enqueue_result_for_all_others(const packet_t& event,
                                          int others_than) {
  for (auto& queue : result_events) {
    if (queue.first != others_than)
      queue.second.enqueue(event);
  }
}

Map& Match::get_map() { return map; }

Player& Match::get_player(int id) { return players.at(id); }

bool Match::has_result_events_left(int id) {
  return !result_events.at(id).is_empty();
}

void Match::eliminate_player(int id) {
  players.erase(id);
  result_events.erase(id); // TODO CHECK THIS! Should problably enqueue kill socket event to notify thread

  if (players.size() == 1)
    events_to_process.enqueue(build_game_over_event());
}

void Match::end() { keep_running = false; }
