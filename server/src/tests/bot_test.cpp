#include "bot_test.h"

#include "../../../common/src/main/packets/packet.h"
#include "../../../common/src/tests/tests_setup.h"
#include "../main/bot/bot.h"
#include "../main/game/objects/rectangular_object.h"
#include "../main/game/player.h"
#include "../main/map.h"
#include "client_mock.h"

//#define MAP_TEST_SIZE 640
#define TEST_MAP_EMPTY "test_map_empty"

int static can_walk_around_alone();
int static can_kill_a_player();
int static can_kill_two_players();
int static can_kill_one_diagonal_player();
int static can_kill_one_diagonal_and_then_walk_a_lot();
int static can_kill_one_far_player();
int static can_kill_multiple_players_in_high_positions();
int static can_kill_multiple_players_in_different_positions();
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
/* Takes too much time
  print_test("El bot mata a varios jugadores en distintos lugares",
               can_kill_multiple_players_in_different_positions, NO_ERROR);
*/
  end_tests();
}
/*
Matrix<int> create_testing_base_map() {
  Matrix<int> map_data(MAP_TEST_SIZE, MAP_TEST_SIZE, 0);
  for (size_t i = 0; i < MAP_TEST_SIZE; i++) {
    map_data(i, 0) = WALL;
    map_data(i, MAP_TEST_SIZE - 1) = WALL;
    map_data(0, i) = WALL;
    map_data(MAP_TEST_SIZE - 1, i) = WALL;
  }
  return map_data;
}*/

int static can_walk_around_alone() {
/*
  Matrix<int> map_data = create_testing_base_map();
  Map map(map_data);
  map.add_spawn_point(50, 50);
  */
  std::string map_name("test_map_bot");
  Map map(map_name);
  map.add_player(3);

  CollisionChecker checker(map);

  BlockingQueue<Packet> queue;
  Bot bot(checker, map, 3, queue);

  for (int j = 0; j < map.get_rows(); j++) {
    for (int i = 0; i < map.get_columns(); i++) {
      bot.load_map(j,i,  map(j, i));
    }
  }

  for (int i = 0; i < 5; ++i) {
    bot.execute();
    bot.update_player();
  }

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

  Bot bot(checker, map, 4, queue);


  for (int j = 0; j < map.get_rows(); j++) {
    for (int i = 0; i < map.get_columns(); i++) {
      bot.load_map(j,i,  map(j, i));
    }
  }

  for (int i = 0; i < 200; ++i) { //200
    //printf("\n\nITERACION NÚMERO %i\n\n", i+1);
    bot.execute();
    bot.update_player();
    //printf("\n");
  }

  if (map.get_player(5).is_dead())
    return NO_ERROR;

  return ERROR;

}

int static can_kill_two_players() {
  /*
  Matrix<int> map_data = create_testing_base_map();
  Map map(map_data);
  map.add_spawn_point(40, 50);
  map.add_player(4);
  map.add_spawn_point(65, 50);
  map.add_player(5);
  map.add_spawn_point(95, 50);
  map.add_player(6);
*/
  std::string map_name("test_map2_bot");
  Map map(map_name);
  map.add_player(6);
  map.add_player(7);
  map.add_player(8);

  CollisionChecker checker(map);
  BlockingQueue<Packet> queue;
  Bot bot(checker, map, 6, queue);

  for (int j = 0; j < map.get_rows(); j++) {
    for (int i = 0; i < map.get_columns(); i++) {
      bot.load_map(j,i,  map(j, i));
    }
  }
  for (int i = 0; i < 500; ++i) {
    //printf("\n\nITERACION NÚMERO %i\n\n", i+1);
    bot.execute();
    bot.update_player();
    //printf("\n");

  }
  if (map.get_player(7).is_dead() && map.get_player(8).is_dead())
    return NO_ERROR;
  return ERROR;

}

int static can_kill_one_diagonal_player() {
  /*
  Matrix<int> map_data = create_testing_base_map();
  Map map(map_data);

  map.add_spawn_point(50, 50);
  map.add_player(7);
  map.add_spawn_point(70, 70);
  map.add_player(8);
*/
  std::string map_name("test_map3_bot");
  Map map(map_name);
  map.add_player(9);
  map.add_player(10);

  CollisionChecker checker(map);
  BlockingQueue<Packet> queue;
  Bot bot(checker, map, 9, queue);

  for (int j = 0; j < map.get_rows(); j++) {
    for (int i = 0; i < map.get_columns(); i++) {
      bot.load_map(j,i,  map(j, i));
    }
  }
  for (int i = 0; i < 300; ++i) {
    //printf("\n\nITERACION NÚMERO %i\n\n", i+1);
    bot.execute();
    bot.update_player();
    //printf("Bot:(%f,%f)", player1.get_position().getX(),
//player1.get_position().getY());
    //printf("P2:(%f,%f)", player2.get_position().getX(),
//player2.get_position().getY());
    //printf("\n");
  }
  if (map.get_player(10).is_dead())
    return NO_ERROR;
  return ERROR;

}

int static can_kill_one_diagonal_and_then_walk_a_lot() {
  /*
  Matrix<int> map_data = create_testing_base_map();
  Map map(map_data);
  map.add_spawn_point(50, 50);
  map.add_player(9);
  map.add_spawn_point(70, 70);
  map.add_player(10);
*/
  std::string map_name("test_map4_bot");
  Map map(map_name);
  map.add_player(11);
  map.add_player(12);

  CollisionChecker checker(map);
  BlockingQueue<Packet> queue;
  Bot bot(checker, map, 11, queue);

  for (int j = 0; j < map.get_rows(); j++) {
    for (int i = 0; i < map.get_columns(); i++) {
      bot.load_map(j,i,  map(j, i));
    }
  }
  for (int i = 0; i < 2000; ++i) {
    //printf("\n\nITERACION NÚMERO %i\n\n", i+1);
    bot.execute();
    bot.update_player();
  }
  if (map.get_player(12).is_dead())
    return NO_ERROR;
  return ERROR;
}

int static can_kill_one_far_player(){
  /*
  Matrix<int> map_data = create_testing_base_map();
  Map map(map_data);
  map.add_spawn_point(25, 40);
  map.add_player(11);
  map.add_spawn_point(118.94, 13);
  map.add_player(12);
*/
  std::string map_name("test_map5_bot");
  Map map(map_name);
  map.add_player(13);
  map.add_player(14);

  CollisionChecker checker(map);
  BlockingQueue<Packet> queue;
  Bot bot(checker, map, 13, queue);

  for (int j = 0; j < map.get_rows(); j++) {
    for (int i = 0; i < map.get_columns(); i++) {
      bot.load_map(j,i,  map(j, i));
    }
  }

  for (int i = 0; i < 10000; ++i) {
    bot.execute();
    bot.update_player();
  }
  if (map.get_player(14).is_dead())
    return NO_ERROR;

  return ERROR;

}

int static can_kill_multiple_players_in_high_positions() {
/*
  Matrix<int> map_data = create_testing_base_map();
  Map map(map_data);

  map.add_spawn_point(500, 500);
  map.add_player(13);
  map.add_spawn_point(390, 600);
  map.add_player(14);
  map.add_spawn_point(425, 501);
  map.add_player(15);
  map.add_spawn_point(502, 450);
  map.add_player(16);
  map.add_spawn_point(550, 550);
  map.add_player(17);
*/
  std::string map_name("test_map6_bot");
  Map map(map_name);
  map.add_player(15);
  map.add_player(16);
  map.add_player(17);
  map.add_player(18);
  map.add_player(19);

  CollisionChecker checker(map);
  BlockingQueue<Packet> queue;
  Bot bot(checker, map, 15, queue);

  for (int j = 0; j < map.get_rows(); j++) {
    for (int i = 0; i < map.get_columns(); i++) {
      bot.load_map(j,i,  map(j, i));
    }
  }
  for (int i = 0; i < 5000; ++i) { //50000
    //printf("\n\nITERACION NÚMERO %i\n\n", i+1);
    bot.execute();
    bot.update_player();
    //printf("\n");
  }

  //printf("%d|%d|%d|%d", map.get_player(14).is_dead(), map.get_player(15).is_dead(),
  //map.get_player(16).is_dead(), map.get_player(17).is_dead());
  if ((map.get_player(16).is_dead()) && (map.get_player(17).is_dead())
      && (map.get_player(18).is_dead()) && (map.get_player(19).is_dead()))
    return NO_ERROR;
  return ERROR;

}

int static can_kill_multiple_players_in_different_positions() {
  /*
  Matrix<int> map_data = create_testing_base_map();
  Map map(map_data);

  map.add_spawn_point(50, 50);
  map.add_player(18);
  map.add_spawn_point(10.1, 10.8);
  map.add_player(19);
  map.add_spawn_point(23.5, 600);
  map.add_player(20);
  map.add_spawn_point(21.19, 77.4);
  map.add_player(21);
  map.add_spawn_point(391.1, 90);
  map.add_player(22);
  map.add_spawn_point(10, 111);
  map.add_player(23);
*/
  std::string map_name("test_map7_bot");
  Map map(map_name);
  map.add_player(20);
  map.add_player(21);
  map.add_player(22);
  map.add_player(23);
  map.add_player(24);
  map.add_player(25);


  CollisionChecker checker(map);
  BlockingQueue<Packet> queue;
  Bot bot(checker, map, 20, queue);

  for (int j = 0; j < map.get_rows(); j++) {
    for (int i = 0; i < map.get_columns(); i++) {
      bot.load_map(j,i,  map(j, i));
    }
  }
  for (int i = 0; i < 5000; ++i) { //50000
    bot.execute();
    bot.update_player();
  }

   if ((map.get_player(21).is_dead()) && (map.get_player(22).is_dead())
      && (map.get_player(23).is_dead()) && (map.get_player(24).is_dead())
      && (map.get_player(25).is_dead()))
    return NO_ERROR;
  return ERROR;
}
