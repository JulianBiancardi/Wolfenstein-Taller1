#include "match.h"

Match::Match(Map& map) : map(map), players_id_count(1) {}

Match::~Match() {}

void Match::add_player(Point where, double initial_angle) {
  players.insert({players_id_count,
                  Player(where, initial_angle, players_id_count)});
  players_id_count++;
}

void Match::enqueue_event(const Event& event) {
  events_to_process.enqueue(event);
}

const Event Match::dequeue_result() { return result_events.dequeue(); }

void Match::start() {
  bool keep_running = true;
  EventHandlerBuilder builder;
  CollisionChecker checker(map, players, map.get_items(), map.get_objects());

  while (keep_running) {
    const Event next_event = events_to_process.dequeue();
    EventHandler* handler = builder.build(next_event, players);
    handler->handle(*this, checker);
    delete handler;

    if (events_to_process.is_empty())  // TODO Change way of ending loop
      keep_running = false;
  }
}

void Match::enqueue_result(const Event& event) { result_events.enqueue(event); }

Map& Match::get_map() { return map; }

Player& Match::get_player(int id) { return players.at(id); }
