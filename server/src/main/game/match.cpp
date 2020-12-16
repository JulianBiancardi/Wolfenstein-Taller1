#include "match.h"

Match::Match(Map &map) : map(map), players_id_count(1), items_id_count(1) {}

Match::~Match() {
  for (auto item : items)
    delete item.second;
}

void Match::add_player(Point where, double initial_angle) {
  players.insert({players_id_count, Player(where, initial_angle)});
  players_id_count++;
}

void Match::add_item(Items *what) {
  items.insert({items_id_count, what});
  items_id_count++;
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

std::vector<Items *>
Match::get_items_as_vector() {
  std::vector<Items *> vector;
  for (auto &item : items) {
    vector.push_back(item.second);
  }
  return vector;
}

void Match::start() {
  bool keep_running = true;
  EventHandlerBuilder builder;
  CollisionChecker checker(map,
                           get_players_as_vector(),
                           sprites,
                           get_items_as_vector());

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

int Match::get_item_id(Items *item) {
  int id = -1;
  for (auto const &element : items) {
    if (element.second == item)
      id = element.first;
  }
  return id;
}

Player &Match::get_player(int id) {
  return players.at(id);
}
