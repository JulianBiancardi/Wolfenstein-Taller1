#include "bot_test.h"

#include "../main/managers/match.h"
#include "../../../common/src/tests/tests_setup.h"
#include "../main/bot/bot.h"
#define TEST_MAP_EMPTY "test_map_empty"

int static can_walk_around_alone();
int static can_kill_a_player();
int static can_kill_two_players();
int static can_kill_one_diagonal_player();
int static can_kill_one_diagonal_and_then_walk_a_lot();
int static can_kill_one_far_player();
int static can_kill_multiple_players_in_high_positions();
int static can_kill_multiple_players_in_different_positions();
int static can_kill_real_map();

void bot_tests() {
  // Tests are not shown using std::cout, use printf instead
  begin_tests("BOT");

  print_test("El bot se mueve solo correctamente", can_walk_around_alone,
             NO_ERROR);

  print_test("El bot mata a un jugador correctamente",
               can_kill_a_player, NO_ERROR);

  print_test("El bot mata a dos jugadores correctamente",
               can_kill_two_players, NO_ERROR);

  print_test("El bot mata a jugador en diagonal correctamente",
               can_kill_one_diagonal_player, NO_ERROR);

  print_test("El bot mata en diagonal y camina mucho correctamente",
               can_kill_one_diagonal_and_then_walk_a_lot, NO_ERROR);

  print_test("El bot mata a un jugador lejano",
               can_kill_one_far_player, NO_ERROR);

  print_test("El bot mata a varios jugadores en posiciones altas del mapa",
               can_kill_multiple_players_in_high_positions, NO_ERROR);

  print_test("El bot mata a varios jugadores en distintos lugares",
               can_kill_multiple_players_in_different_positions, NO_ERROR);

  print_test("El bot mata en mapa real",
             can_kill_real_map, NO_ERROR);

  end_tests();
}

int static can_walk_around_alone() {
  std::string map_name("test_map_bot");
  Map map(map_name);
  map.add_player(3);

  CollisionChecker checker(map);

  BlockingQueue<Packet> queue;
  Match * match = new Match(1, 1, map_name);
  Bot bot(checker, map, 3, queue, match);

  for (int j = 0; j < map.get_rows(); j++) {
    for (int i = 0; i < map.get_columns(); i++) {
      bot.load_map(j,i,  map(j, i));
    }
  }

  for (int i = 0; i < 5; ++i) {
    bot.execute();
    bot.update_player();
  }
  delete match;
  if ((map.get_player(3).get_position().getX() > 26
      && map.get_player(3).get_position().getX() < 38)
      && (map.get_player(3).get_position().getY() > 26
          && map.get_player(3).get_position().getY() < 38)
      )
    return NO_ERROR;

  return ERROR;
}

int static can_kill_a_player(){
  std::string map_name("test_map1_bot");
  Map map(map_name);
  map.add_player(4);
  map.add_player(5);

  CollisionChecker checker(map);
  BlockingQueue<Packet> queue;
  Match * match = new Match(2, 1, map_name);
  Bot bot(checker, map, 4, queue, match);


  for (int j = 0; j < map.get_rows(); j++) {
    for (int i = 0; i < map.get_columns(); i++) {
      bot.load_map(j,i,  map(j, i));
    }
  }

  for (int i = 0; i < 200; ++i) {
    bot.execute();
    bot.update_player();
  }
  delete match;
  if (map.get_player(5).is_dead())
    return NO_ERROR;

  return ERROR;

}

int static can_kill_two_players() {
  std::string map_name("test_map2_bot");
  Map map(map_name);
  map.add_player(6);
  map.add_player(7);
  map.add_player(8);

  CollisionChecker checker(map);
  BlockingQueue<Packet> queue;
  Match * match = new Match(3, 1, map_name);
  Bot bot(checker, map, 6, queue, match);

  for (int j = 0; j < map.get_rows(); j++) {
    for (int i = 0; i < map.get_columns(); i++) {
      bot.load_map(j,i,  map(j, i));
    }
  }
  for (int i = 0; i < 500; ++i) {
    bot.execute();
    bot.update_player();
  }
  delete match;
  if (map.get_player(7).is_dead() && map.get_player(8).is_dead())
    return NO_ERROR;
  return ERROR;

}

int static can_kill_one_diagonal_player() {
  std::string map_name("test_map3_bot");
  Map map(map_name);
  map.add_player(9);
  map.add_player(10);

  CollisionChecker checker(map);
  BlockingQueue<Packet> queue;
  Match * match = new Match(4, 1, map_name);
  Bot bot(checker, map, 9, queue, match);

  for (int j = 0; j < map.get_rows(); j++) {
    for (int i = 0; i < map.get_columns(); i++) {
      bot.load_map(j,i,  map(j, i));
    }
  }
  for (int i = 0; i < 300; ++i) {
    bot.execute();
    bot.update_player();
  }
  delete match;
  if (map.get_player(10).is_dead())
    return NO_ERROR;
  return ERROR;

}

int static can_kill_one_diagonal_and_then_walk_a_lot() {
  std::string map_name("test_map4_bot");
  Map map(map_name);
  map.add_player(11);
  map.add_player(12);

  CollisionChecker checker(map);
  BlockingQueue<Packet> queue;
  Match * match = new Match(5, 1, map_name);
  Bot bot(checker, map, 11, queue, match);

  for (int j = 0; j < map.get_rows(); j++) {
    for (int i = 0; i < map.get_columns(); i++) {
      bot.load_map(j,i,  map(j, i));
    }
  }
  for (int i = 0; i < 2000; ++i) {
    bot.execute();
    bot.update_player();
  }
  delete match;
  if (map.get_player(12).is_dead())
    return NO_ERROR;
  return ERROR;
}

int static can_kill_one_far_player(){
  std::string map_name("test_map5_bot");
  Map map(map_name);
  map.add_player(13);
  map.add_player(14);

  CollisionChecker checker(map);
  BlockingQueue<Packet> queue;
  Match * match = new Match(6, 1, map_name);
  Bot bot(checker, map, 13, queue, match);

  for (int j = 0; j < map.get_rows(); j++) {
    for (int i = 0; i < map.get_columns(); i++) {
      bot.load_map(j,i,  map(j, i));
    }
  }

  for (int i = 0; i < 10000; ++i) {
    bot.execute();
    bot.update_player();
  }
  delete match;
  if (map.get_player(14).is_dead())
    return NO_ERROR;
  return ERROR;

}

int static can_kill_multiple_players_in_high_positions() {
  std::string map_name("test_map6_bot");
  Map map(map_name);
  map.add_player(15);
  map.add_player(16);
  map.add_player(17);
  map.add_player(18);
  map.add_player(19);

  CollisionChecker checker(map);
  BlockingQueue<Packet> queue;
  Match * match = new Match(7, 1, map_name);
  Bot bot(checker, map, 15, queue, match);

  for (int j = 0; j < map.get_rows(); j++) {
    for (int i = 0; i < map.get_columns(); i++) {
      bot.load_map(j,i,  map(j, i));
    }
  }
  for (int i = 0; i < 5000; ++i) {
    bot.execute();
    bot.update_player();
  }
  delete match;
  if ((map.get_player(16).is_dead()) &&
      (map.get_player(17).is_dead()) &&
      (map.get_player(18).is_dead()) &&
      (map.get_player(19).is_dead()))
    return NO_ERROR;
  return ERROR;

}

int static can_kill_multiple_players_in_different_positions() {
  std::string map_name("test_map7_bot");
  Map map(map_name);
  map.add_player(20);
  map.add_player(21);
  map.add_player(22);
  map.add_player(23);
  map.add_player(24);

  CollisionChecker checker(map);
  BlockingQueue<Packet> queue;
  Match * match = new Match(8, 1, map_name);
  Bot bot(checker, map, 20, queue, match);

  for (int j = 0; j < map.get_rows(); j++) {
    for (int i = 0; i < map.get_columns(); i++) {
      bot.load_map(j,i,  map(j, i));
    }
  }
  for (int i = 0; i < 5000; ++i) {
    bot.execute();
    bot.update_player();
  }
  delete match;
  if ((map.get_player(21).is_dead()) &&
      (map.get_player(22).is_dead()) &&
      (map.get_player(23).is_dead()) &&
      (map.get_player(24).is_dead()))
    return NO_ERROR;
  return ERROR;
}

int static can_kill_real_map(){
  //std::string map_name("test_map_dog");
  std::string map_name("map_bot_new");
  Map map(map_name);
  map.add_player(25);
  map.add_player(26);

  CollisionChecker checker(map);
  BlockingQueue<Packet> queue;
  Match * match = new Match(2, 1, map_name);
  Bot bot(checker, map, 25, queue, match);


  for (int j = 0; j < map.get_rows(); j++) {
    for (int i = 0; i < map.get_columns(); i++) {
      bot.load_map(j,i,  map(j, i));
    }
  }

  for (int i = 0; i < 500; ++i) {
    bot.execute();
    bot.update_player();
  }
  delete match;
  if (map.get_player(26).is_dead())
    return NO_ERROR;

  return ERROR;

}