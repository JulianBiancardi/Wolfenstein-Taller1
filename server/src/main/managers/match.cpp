#include "match.h"

#include "../game/objects/door/door.h"
#include "../threads/bot_thread.h"
#include "../threads/clock/clock_thread.h"
#include "match_error.h"

#define CLOCK_KEY 0
Match::Match(unsigned int host_id, unsigned char match_id,
             std::string& map_name)
    : host_id(host_id),
      map(map_name),
      checker(map),
      started(false),
      match_id(match_id) {}

Match::~Match() {
  if (started) {
    ((ClockThread*)threads.at(CLOCK_KEY))->force_stop();

    for (auto thread : threads) {
      thread.second->join();
    }
  }

  for (auto thread : threads) {
    delete thread.second;
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

const std::unordered_map<unsigned int, Item*>& Match::get_items() const {
  return map.get_items();
}

unsigned char Match::get_id() const { return match_id; }

const std::string& Match::get_map_name() const { return map.get_name(); }

unsigned char Match::get_capacity() const { return map.get_capacity(); }

bool Match::has_started() const { return started; }

bool Match::start(unsigned int player_id, BlockingQueue<Packet>& queue) {
  if (player_id == host_id) {
    if (!started) {
      started = true;

      auto clock = new ClockThread(CL::match_length, queue, match_id);
      threads.insert({CLOCK_KEY, clock});

      for (unsigned int i = players_ids.size() + 1;
           i < players_ids.size() + 1 + map.get_dogs_amount(); i++) {
        if (this->add_bot(i)) {
          auto bot = new BotThread(checker, map, i, queue, this);
          threads.insert({i, bot});
        }
      }

      for (auto thread : threads) {
        thread.second->start();
      }

      return true;
    } else {
      return false;
    }
  } else {
    throw MatchError("Failed to start match. Player isn't Host.");
  }
}

bool Match::add_bot(unsigned int player_id) {
  if (map.add_bot(player_id)) {
    players_ids.insert(player_id);
    return true;
  } else {
    return false;
  }
}

bool Match::add_player(unsigned int player_id) {
  if (started) {
    return false;
  }
  if (map.add_player(player_id)) {
    players_ids.insert(player_id);
    return true;
  } else {
    return false;
  }
}

bool Match::move_player(unsigned int player_id, unsigned char direction) {
  if (!started) {
    throw MatchError("Failed to move player. Match hasn't started.");
  }

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
  if (!started) {
    throw MatchError("Failed to rotate player. Match hasn't started.");
  }

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

  if (is_dead(player_id)) {
    return 0;
  }

  Player& player = map.get_player(player_id);
  unsigned int item_id = checker.grabbed_item(player);

  if (item_id != 0) {
    Item& item = map.get_item(item_id);

    if (item.can_be_used_by(player)) {
      item.use(player);
      map.delete_item(item_id);

      return item_id;
    }
  }

  return 0;
}

bool Match::change_gun(unsigned int player_id, unsigned char gun_id) {
  if (!started) {
    throw MatchError("Failed to change gun. Match hasn't started.");
  }

  if (!player_exists(player_id)) {
    throw MatchError("Failed to change gun player. Player %u doesn't exist.",
                     player_id);
  }

  if (is_dead(player_id)) {
    return false;
  }

  // TODO Check if he has enough bullets to wield it
  return map.get_player(player_id).change_gun(gun_id);
}

void Match::damage_player(unsigned int player_id, unsigned int damager_id,
                          unsigned char damage) {
  if (!started) {
    throw MatchError("Failed to damage player. Match hasn't started.");
  }

  if (!player_exists(player_id)) {
    throw MatchError("Failed to damage player. Player %u doesn't exist.",
                     player_id);
  }

  if (!player_exists(damager_id)) {
    throw MatchError("Failed to damage player. Player %u doesn't exist.",
                     damager_id);
  }

  if (is_dead(player_id)) {
    return;
  }

  Player& player = map.get_player(player_id);

  player.receive_damage(damage);

  if (player.is_dead()) {
    kill_player(player_id);
    Player& damager = map.get_player(damager_id);
    damager.add_kill();
  }
}

void Match::shoot_gun(unsigned int player_id, unsigned int objective_id,
                      unsigned char damage) {
  if (!started) {
    throw MatchError("Failed to shoot gun. Match hasn't started.");
  }

  if (!player_exists(player_id)) {
    throw MatchError("Failed to shoot gun. Player %u doesn't exist.",
                     player_id);
  }

  if (objective_id != 0 && !player_exists(objective_id)) {
    throw MatchError("Failed to shoot at player. Player %u doesn't exist.",
                     objective_id);
  }

  if (is_dead(player_id)) {
    return;
  }

  Player& shooter = map.get_player(player_id);

  if (!shooter.shoot()) {
    throw MatchError(
        "Failed to shoot gun. Player %u doesn't have enough bullets.",
        player_id);
  }

  if (objective_id != 0) {
    damage_player(objective_id, player_id, damage);
  }
}

bool Match::is_using_rocket_launcher(unsigned int player_id) {
  if (!started) {
    throw MatchError(
        "Failed to check if player can launch rocket. "
        "Match hasn't started.");
  }

  if (!player_exists(player_id)) {
    throw MatchError(
        "Failed to check if player can launch rocket. "
        "Player %u doesn't exist.",
        player_id);
  }

  if (is_dead(player_id)) {
    return false;
  }

  Player& player = map.get_player(player_id);

  return player.is_using_rocket_launcher();
}

void Match::shoot_rocket(unsigned int player_id) {
  if (!player_exists(player_id)) {
    throw MatchError("Failed to create rocket. Player %u doesn't exist.",
                     player_id);
  }

  if (is_dead(player_id)) {
    return;
  }

  Player& shooter = map.get_player(player_id);

  if (!shooter.shoot()) {
    throw MatchError(
        "Failed to shoot gun. Player %u doesn't have enough bullets.",
        player_id);
  }

  Point spawn_point = shooter.collision_mask_bound(shooter.next_position(UP));
  double spawn_angle = shooter.get_angle();

  unsigned int rocket_id = map.add_rocket(spawn_point, spawn_angle);
  ((ClockThread*)threads.at(CLOCK_KEY))
      ->add_rocket_controller(rocket_id, player_id);
}

bool Match::move_rocket(unsigned int rocket_id) {
  if (!map.object_exists(rocket_id)) {
    throw MatchError("Failed to move rocket. Rocket %u doesn't exist.",
                     rocket_id);
  }

  auto rocket = (Moveable*)map.get_object(rocket_id);

  Point next_position = rocket->next_position(UP);
  if (checker.can_move(next_position, *rocket)) {
    rocket->set_position(next_position);

    return true;
  } else {
    return false;
  }
}

unsigned char calculate_damage(Moveable& rocket, Player& player) {
  Point rocket_center = rocket.get_position();
  Point player_center = player.get_position();

  double distance = rocket_center.distance_from(player_center);

  /* Damage(distance) = a / distance + b
   * Damage(CL::player_mask_radio) = CL::rocket_max_damage
   * Damage(CL::rocket_explosion_radius) = CL::rocket_min_damage
   */
  double b = (CL::rocket_min_damage * CL::rocket_explosion_radius -
              CL::rocket_max_damage * CL::player_mask_radio) /
             (CL::rocket_max_damage - CL::rocket_min_damage);
  double a = CL::rocket_max_damage * (CL::player_mask_radio + b);

  return (unsigned char)(a / (distance + b));
}

std::map<unsigned int, unsigned char> Match::explode_rocket(
    unsigned int rocket_id, unsigned int owner_id) {
  if (!map.object_exists(rocket_id)) {
    throw MatchError("Failed to explode rocket. Rocket %u doesn't exist.",
                     rocket_id);
  }

  auto rocket = (Moveable*)map.get_object(rocket_id);

  Point next_position = rocket->next_position(UP);
  std::vector<unsigned int> players_exploded =
      checker.get_players_in_radius(next_position, CL::rocket_explosion_radius);

  std::map<unsigned int, unsigned char> return_map;

  for (auto id : players_exploded) {
    Player& player = map.get_player(id);
    unsigned char damage = calculate_damage(*rocket, player);

    damage_player(id, owner_id, damage);

    return_map.insert(std::make_pair(id, damage));
  }

  map.delete_object(rocket_id);
  ((ClockThread*)threads.at(CLOCK_KEY))->delete_rocket_controller(rocket_id);

  return return_map;
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

  map.add_drop(player);

  if (player.has_extra_lives()) {
    player.respawn();
  } else {
    player.respawn_as_ghost();
  }
}

bool Match::has_lives(unsigned int player_id) {
  if (!player_exists(player_id)) {
    throw MatchError("Failed to check lives. Player %u doesn't exist.",
                     player_id);
  }

  if (is_dead(player_id)) {
    return false;
  }

  return map.get_player(player_id).has_extra_lives();
}

bool Match::interact_with_door(unsigned int player_id) {
  if (!player_exists(player_id)) {
    throw MatchError("Failed to find door interactor. Player %u doesn't exist.",
                     player_id);
  }

  if (is_dead(player_id)) {
    return false;
  }

  Player& player = map.get_player(player_id);

  Point forward = player.next_position(UP);
  std::pair<unsigned int, unsigned int> cell(forward.getX(), forward.getY());
  std::shared_ptr<Door>& door = map.get_door(cell);

  if (!checker.is_free(door->get_position())) {
    return false;
  }

  if (door->interact(player, checker)) {
    if (door->is_open()) {
      ((ClockThread*)threads.at(CLOCK_KEY))->add_door_timer(cell);
    }
    return true;
  } else {
    return false;
  }
}

bool Match::close_door(unsigned int door_id) {
  if (!map.object_exists(door_id)) {
    throw MatchError("Failed to find door. Door %u doesn't exist.", door_id);
  }

  auto door = (Door*)map.get_object(door_id);

  door->close(checker);

  if (!door->is_open()) {
    ((ClockThread*)threads.at(CLOCK_KEY))->delete_door_timer(door_id);
    return true;
  } else {
    return false;
  }
}

void Match::delete_player(unsigned int player_id) {
  if (!player_exists(player_id)) {
    throw MatchError("Failed to delete player. Player %u doesn't exist.",
                     player_id);
  }

  players_ids.erase(player_id);
}

bool Match::should_end() const { return map.has_one_player_alive(); }
