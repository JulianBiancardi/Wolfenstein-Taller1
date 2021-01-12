#include "match.h"

Match::Match(Map& map) : map(map), players_id_count(1) {}

Match::~Match() {}

void Match::add_player(Point where, double initial_angle) {
  players.insert({players_id_count,
                  Player(where, initial_angle, players_id_count)});
  result_events.emplace(std::piecewise_construct,
                        std::forward_as_tuple(players_id_count),
                        std::forward_as_tuple()); // In-place construction
  players_id_count++;
}

void Match::enqueue_event(const packet_t& event) {
  events_to_process.enqueue(event);
}

const packet_t Match::dequeue_result(int for_whom) {
  return result_events.at(for_whom).dequeue(); // Throws out_of_range if not found
}

void Match::start() {
  bool keep_running = true;
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

// Check if it is used (now is NOT being used)
void Match::enqueue_result_for_all_others(const packet_t& event,
                                          int others_than) {
  for (auto& queue : result_events) {
    if (queue.first != others_than)
      queue.second.enqueue(event);
  }
}

Map& Match::get_map() { return map; }

Player& Match::get_player(int id) { return players.at(id); }
