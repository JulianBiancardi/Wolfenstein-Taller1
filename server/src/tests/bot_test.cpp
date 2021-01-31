#include "bot_test.h"

#include "../../../common/src/main/packets/packet.h"
#include "../../../common/src/tests/tests_setup.h"
#include "../main/bot.h"
#include "../main/game/objects/rectangular_object.h"
#include "../main/game/player.h"
#include "../main/map.h"
#include "client_mock.h"

int static can_walk_around_alone();
int static can_kill_a_player();
int static can_kill_two_players();
int static can_kill_one_diagonal_player();
int static can_kill_one_diagonal_and_then_walk_a_lot();
int static can_kill_multiple_players_in_different_positions();
int static can_kill_one_far_player();
int static can_kill_multiple_far_players();
void bot_tests() {
  // Tests are not shown using std::cout, use printf instead
  begin_tests("BOT");

  print_test("El bot se mueve solo correctamente", can_walk_around_alone,
             NO_ERROR);
  /*
    print_test("El bot mata a un jugador correctamente",
               can_kill_a_player, NO_ERROR);

    print_test("El bot mata a dos jugadores correctamente",
               can_kill_two_players, NO_ERROR);

    print_test("El bot mata a jugador en diagonal correctamente",
               can_kill_one_diagonal_player, NO_ERROR);

    print_test("El bot mata en diagonal y camina mucho correctamente",
               can_kill_one_diagonal_and_then_walk_a_lot, NO_ERROR);

    print_test("El bot mata a varios jugadores en distintos lugares",
               can_kill_multiple_players_in_different_positions, NO_ERROR);
  */

  end_tests();
}

int static can_walk_around_alone() {
  Matrix<int> map_data(640, 640, 0);  // Emulates map loaded

  put_data_on_borders(map_data);
  Map map(map_data);

  Player player1(50, 50, M_PI / 2);

  map.add_player(player1.get_id());
  /*

    std::unordered_map<int, Player> players;
    players.insert({1, player1});

    std::vector<Object*> sprites;
    std::unordered_map<int, Item*> items;



    CollisionChecker checker(map, players, items, sprites);

    Bot bot(checker, players.at(1), players);
    bot.set_id_at_players(1);

    for (int j = 0; j < map_data.get_rows(); j++) {
      for (int i = 0; i < map_data.get_columns(); i++) {
        bot.load_map(j,i,  map_data(j, i));
      }
    }
    for (int i = 0; i < 10; ++i) {
      bot.execute();
      bot.update_player();
    }
    if ((players.at(1).get_position().getX() > 39
        && players.at(1).get_position().getX() < 61)
        && (players.at(1).get_position().getY() > 39
            && players.at(1).get_position().getY() < 61)
        )
      return NO_ERROR;
    */

  return ERROR;
}
/*
int static can_kill_a_player(){
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data_on_borders(map_data);
  Map map(map_data);
  Player player1(50, 50, M_PI / 2);
  Player player2(65, 50, M_PI / 2);

  std::unordered_map<int, Player> players;
  players.insert({1, player1});
  players.insert({2, player2});

  std::vector<Object*> sprites;
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map, players, items, sprites);

  Bot bot(checker, players.at(1), players);
  bot.set_id_at_players(1);

  for (int j = 0; j < map_data.get_rows(); j++) {
    for (int i = 0; i < map_data.get_columns(); i++) {
      bot.load_map(j,i,  map_data(j, i));
    }
  }

  for (int i = 0; i < 20; ++i) {
    //printf("\n\nITERACION NÚMERO %i\n\n", i+1);
    bot.execute();
    bot.update_player();
    //printf("|%d|", players.at(2).is_dead());
    //printf("\n");
  }
  if (players.at(2).is_dead())
    return NO_ERROR;

  return ERROR;

}


int static can_kill_two_players() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data_on_borders(map_data);
  Map map(map_data);
  Player player1(40, 50, M_PI / 2);
  Player player2(65, 50, M_PI / 2);
  Player player3(95, 50, M_PI / 2);

  std::unordered_map<int, Player> players;
  players.insert({1, player1});
  players.insert({2, player2});
  players.insert({3, player3});

  std::vector<Object*> sprites;
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map, players, items, sprites);

  Bot bot(checker, players.at(1), players);
  bot.set_id_at_players(1);

  for (int j = 0; j < map_data.get_rows(); j++) {
    for (int i = 0; i < map_data.get_columns(); i++) {
      bot.load_map(j,i,  map_data(j, i));
    }
  }
  for (int i = 0; i < 90; ++i) {
    //printf("\n\nITERACION NÚMERO %i\n\n", i+1);
    bot.execute();
    bot.update_player();
    //printf("\n");

  }
  if (players.at(2).is_dead() && players.at(3).is_dead())
    return NO_ERROR;
  return ERROR;
}

int static can_kill_one_diagonal_player() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data_on_borders(map_data);
  Map map(map_data);
  Player player1(50, 50, M_PI / 2);
  Player player2(70, 70, M_PI / 2);

  std::unordered_map<int, Player> players;
  players.insert({1, player1});
  players.insert({2, player2});

  std::vector<Object*> sprites;
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map, players, items, sprites);

  Bot bot(checker, players.at(1), players);
  bot.set_id_at_players(1);

  for (int j = 0; j < map_data.get_rows(); j++) {
    for (int i = 0; i < map_data.get_columns(); i++) {
      bot.load_map(j,i,  map_data(j, i));
    }
  }
  for (int i = 0; i < 40; ++i) {
    //printf("\n\nITERACION NÚMERO %i\n\n", i+1);
    bot.execute();
    bot.update_player();
    //printf("Bot:(%f,%f)", player1.get_position().getX(),
player1.get_position().getY());
    //printf("P2:(%f,%f)", player2.get_position().getX(),
player2.get_position().getY());
    //printf("\n");
  }
  if (players.at(2).is_dead())
    return NO_ERROR;
  return ERROR;
}


int static can_kill_one_diagonal_and_then_walk_a_lot() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data_on_borders(map_data);
  Map map(map_data);
  Player player1(50, 50, M_PI / 2);
  Player player2(70, 70, M_PI / 2);

  std::unordered_map<int, Player> players;
  players.insert({1, player1});
  players.insert({2, player2});

  std::vector<Object*> sprites;
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map, players, items, sprites);

  Bot bot(checker, players.at(1), players);
  bot.set_id_at_players(1);

  for (int j = 0; j < map_data.get_rows(); j++) {
    for (int i = 0; i < map_data.get_columns(); i++) {
      bot.load_map(j,i,  map_data(j, i));
    }
  }
  for (int i = 0; i < 200; ++i) {
    //printf("\n\nITERACION NÚMERO %i\n\n", i+1);
    bot.execute();
    bot.update_player();
  }
  if (players.at(2).is_dead())
    return NO_ERROR;
  return ERROR;
}

int static can_kill_multiple_players_in_different_positions() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data_on_borders(map_data);
  Map map(map_data);
  Player player1(50, 50, M_PI / 2);
  Player player2(10.1, 10.8, M_PI / 2); //Muerto
  Player player3(23.5, 99.8, M_PI / 2); //Muerto
  Player player4(21.19, 77.4, M_PI / 2); //Muerto
  Player player5(391.1, 90, M_PI / 2); //Muerto
  Player player6(10, 111, M_PI / 2);

  std::unordered_map<int, Player> players;
  players.insert({1, player1});
  players.insert({2, player2});
  players.insert({3, player3});
  players.insert({4, player4});
  players.insert({5, player5});
  players.insert({6, player6});

  std::vector<Object*> sprites;
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map, players, items, sprites);

  Bot bot(checker, players.at(1), players);
  bot.set_id_at_players(1);

  for (int j = 0; j < map_data.get_rows(); j++) {
    for (int i = 0; i < map_data.get_columns(); i++) {
      bot.load_map(j,i,  map_data(j, i));
    }
  }
  for (int i = 0; i < 1000; ++i) {
    bot.execute();
    bot.update_player();
  }
  if ((players.at(2).is_dead()) && (players.at(3).is_dead())
      && (players.at(4).is_dead()) && (players.at(5).is_dead())
      && (players.at(6).is_dead()))
    return NO_ERROR;
  return ERROR;
}
*/