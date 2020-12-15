#include "match.h"

Match::Match(Map &map) : map(map), id_count(1) {}

void Match::add_player(Point where, double initial_angle) {
  players.insert({id_count, Player(where, initial_angle)});
  id_count++;
}

void Match::enqueue_event(const Event &event) {
  events_to_process.enqueue(event);
}

const Event Match::dequeue_result() {
  return result_events.dequeue();
}

std::vector<std::reference_wrapper<Player>>
Match::get_players_as_vector() {
  std::vector<std::reference_wrapper<Player>> vector;
  for (auto &player : players)
    vector.push_back(player.second);
  return vector;
}

void Match::start() {
  bool keep_running = true;
  EventHandlerBuilder builder;
  CollisionChecker checker(map, get_players_as_vector(), sprites);

  while (keep_running) {
    const Event next_event = events_to_process.dequeue();
    EventHandler *handler = builder.build(next_event, players);
    handler->handle(*this, checker);
    delete handler;

    if (events_to_process.is_empty()) // TODO Change way of ending loop
      keep_running = false;
  }
}

void Match::enqueue_result(const Event &event) {
  result_events.enqueue(event);
}

int Match::get_player_id(Player &player) {
  int id = -1;
  for (auto const &element : players) {
    if (&element.second == &player)
      id = element.first;
  }
  return id;
}
