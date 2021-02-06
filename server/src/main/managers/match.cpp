#include "match.h"

#include "../game/objects/door/door.h"
#include "match_error.h"

Match::Match(unsigned int host_id, unsigned char match_id,
             std::string& map_name)
    : host_id(host_id),
      map(map_name),
      checker(map),
      started(false),
      match_id(match_id) {}

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

bool Match::start(unsigned int player_id) {
  if (player_id == host_id) {
    if (!started) {
      started = true;
      return true;
    } else {
      return false;
    }
  } else {
    throw MatchError("Failed to start match. Player isn't Host.");
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

  // TODO Check if he has enough bullets to wield it
  return map.get_player(player_id).change_gun(gun_id);
}

bool Match::shoot_gun(unsigned int player_id, unsigned int objective_id,
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

  map.add_drop(player);

  if (player.has_extra_lives()) {
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

  return map.get_player(player_id).has_extra_lives();
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

void Match::delete_player(unsigned int player_id) {  // TODO Finish this
  if (!player_exists(player_id)) {
    throw MatchError("Failed to delete player. Player %u doesn't exist.",
                     player_id);
  }

  map.delete_player(player_id);
  players_ids.erase(player_id);
}

bool Match::should_end() const { return map.has_one_player(); }

void Match::end() {
  // TODO
}
