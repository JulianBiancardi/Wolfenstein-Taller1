#include "bot_test.h"

#include "../../../common/src/main/packets/packet.h"
#include "../../../common/src/tests/tests_setup.h"
#include "../main/bot.h"
#include "../main/game/objects/rectangular_object.h"
#include "../main/game/player.h"
#include "../main/map.h"
#include "client_mock.h"

#define MAP_TEST_SIZE 640

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

Matrix<int> create_testing_base_map() {
  Matrix<int> map_data(MAP_TEST_SIZE, MAP_TEST_SIZE, 0);
  for (size_t i = 0; i < MAP_TEST_SIZE; i++) {
    map_data(i, 0) = WALL;
    map_data(i, MAP_TEST_SIZE - 1) = WALL;
    map_data(0, i) = WALL;
    map_data(MAP_TEST_SIZE - 1, i) = WALL;
  }
  return map_data;
}

int static can_walk_around_alone() {
  Matrix<int> map_data = create_testing_base_map();
  Map map(map_data);
  map.add_spawn_point(50, 50);
  map.add_player(1);
  CollisionChecker checker(map);

  Bot bot(checker, map, 1);


  for (int j = 0; j < map_data.get_rows(); j++) {
    for (int i = 0; i < map_data.get_columns(); i++) {
      bot.load_map(j,i,  map_data(j, i));
    }
  }

  for (int i = 0; i < 10/*10*/; ++i) {
    bot.execute();
    bot.update_player();
  }

  if ((map.get_player(1).get_position().getX() > 39
      && map.get_player(1).get_position().getX() < 61)
      && (map.get_player(1).get_position().getY() > 39
          && map.get_player(1).get_position().getY() < 61)
      )
    return NO_ERROR;

  return ERROR;
}

int static can_kill_a_player(){
  Matrix<int> map_data = create_testing_base_map();
  Map map(map_data);
  map.add_spawn_point(50, 50);
  map.add_player(2);
  map.add_spawn_point(65, 50);
  map.add_player(3);

  CollisionChecker checker(map);

  Bot bot(checker, map, 2);

  for (int j = 0; j < map_data.get_rows(); j++) {
    for (int i = 0; i < map_data.get_columns(); i++) {
      bot.load_map(j,i,  map_data(j, i));
    }
  }

  for (int i = 0; i < 200/*200*/; ++i) {
    //printf("\n\nITERACION NÚMERO %i\n\n", i+1);
    bot.execute();
    bot.update_player();
    //printf("\n");
  }
  if (map.get_player(3).is_dead())
    return NO_ERROR;

  return ERROR;
}

int static can_kill_two_players() {
  Matrix<int> map_data = create_testing_base_map();
  Map map(map_data);
  map.add_spawn_point(40, 50);
  map.add_player(4);
  map.add_spawn_point(65, 50);
  map.add_player(5);
  map.add_spawn_point(95, 50);
  map.add_player(6);

  CollisionChecker checker(map);

  Bot bot(checker, map, 4);

  for (int j = 0; j < map_data.get_rows(); j++) {
    for (int i = 0; i < map_data.get_columns(); i++) {
      bot.load_map(j,i,  map_data(j, i));
    }
  }
  for (int i = 0; i < 500/*500*/; ++i) {
    //printf("\n\nITERACION NÚMERO %i\n\n", i+1);
    bot.execute();
    bot.update_player();
    //printf("\n");

  }
  if (map.get_player(5).is_dead() && map.get_player(6).is_dead())
    return NO_ERROR;
  return ERROR;
}

int static can_kill_one_diagonal_player() {
  Matrix<int> map_data = create_testing_base_map();
  Map map(map_data);

  map.add_spawn_point(50, 50);
  map.add_player(7);
  map.add_spawn_point(70, 70);
  map.add_player(8);

  CollisionChecker checker(map);

  Bot bot(checker, map, 7);

  for (int j = 0; j < map_data.get_rows(); j++) {
    for (int i = 0; i < map_data.get_columns(); i++) {
      bot.load_map(j,i,  map_data(j, i));
    }
  }
  for (int i = 0; i < 300/*300*/; ++i) {
    //printf("\n\nITERACION NÚMERO %i\n\n", i+1);
    bot.execute();
    bot.update_player();
    //printf("Bot:(%f,%f)", player1.get_position().getX(),
//player1.get_position().getY());
    //printf("P2:(%f,%f)", player2.get_position().getX(),
//player2.get_position().getY());
    //printf("\n");
  }
  if (map.get_player(8).is_dead())
    return NO_ERROR;
  return ERROR;
}

int static can_kill_one_diagonal_and_then_walk_a_lot() {
  Matrix<int> map_data = create_testing_base_map();
  Map map(map_data);
  map.add_spawn_point(50, 50);
  map.add_player(9);
  map.add_spawn_point(70, 70);
  map.add_player(10);

  CollisionChecker checker(map);

  Bot bot(checker, map, 9);

  for (int j = 0; j < map_data.get_rows(); j++) {
    for (int i = 0; i < map_data.get_columns(); i++) {
      bot.load_map(j,i,  map_data(j, i));
    }
  }
  for (int i = 0; i < 200/*200*/; ++i) {
    //printf("\n\nITERACION NÚMERO %i\n\n", i+1);
    bot.execute();
    bot.update_player();
  }
  if (map.get_player(10).is_dead())
    return NO_ERROR;
  return ERROR;
}

int static can_kill_one_far_player(){
  Matrix<int> map_data = create_testing_base_map();
  Map map(map_data);
  map.add_spawn_point(25, 40);
  map.add_player(11);
  map.add_spawn_point(118.94, 13);
  map.add_player(12);

  CollisionChecker checker(map);

  Bot bot(checker, map, 11);

  for (int j = 0; j < map_data.get_rows(); j++) {
    for (int i = 0; i < map_data.get_columns(); i++) {
      bot.load_map(j,i,  map_data(j, i));
    }
  }

  for (int i = 0; i < 10000/*10000*/; ++i) {
    bot.execute();
    bot.update_player();
  }
  if (map.get_player(12).is_dead())
    return NO_ERROR;

  return ERROR;
}

int static can_kill_multiple_players_in_high_positions() {
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


  CollisionChecker checker(map);

  Bot bot(checker, map, 13);

  for (int j = 0; j < map_data.get_rows(); j++) {
    for (int i = 0; i < map_data.get_columns(); i++) {
      bot.load_map(j,i,  map_data(j, i));
    }
  }
  for (int i = 0; i < 50000; ++i) {
    //printf("\n\nITERACION NÚMERO %i\n\n", i+1);
    bot.execute();
    bot.update_player();
    //printf("\n");
  }

  //printf("%d|%d|%d|%d", map.get_player(14).is_dead(), map.get_player(15).is_dead(),
  //map.get_player(16).is_dead(), map.get_player(17).is_dead());
  if ((map.get_player(14).is_dead()) && (map.get_player(15).is_dead())
      && (map.get_player(16).is_dead()) && (map.get_player(17).is_dead()))
    return NO_ERROR;
  return ERROR;
}

int static can_kill_multiple_players_in_different_positions() {
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


  CollisionChecker checker(map);

  Bot bot(checker, map, 18);

  for (int j = 0; j < map_data.get_rows(); j++) {
    for (int i = 0; i < map_data.get_columns(); i++) {
      bot.load_map(j,i,  map_data(j, i));
    }
  }
  for (int i = 0; i < 50000; ++i) {
    bot.execute();
    bot.update_player();
  }

   if ((map.get_player(19).is_dead()) && (map.get_player(20).is_dead())
      && (map.get_player(21).is_dead()) && (map.get_player(22).is_dead())
      && (map.get_player(23).is_dead()))
    return NO_ERROR;
  return ERROR;
}
