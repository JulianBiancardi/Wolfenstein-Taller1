#include "client.h"

#include <QtWidgets/QApplication>

#include "../../../common/src/main/config_loader.h"
#include "game.h"
#include "launcher/include/mainwindow.h"
#include "server.h"

Client::Client() {}

Client::~Client() {}

void Client::run_client(int argc, char** argv) {
  Server server;
  Match match_selected;

  try {
    QApplication main_app(argc, argv);
    MainWindow main_window(nullptr, &server, &match_selected);
    main_window.show();
    main_window.update();
    main_app.exec();

  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  if (!match_selected.is_valid()) {
    return;
  }

  match_selected.print();

  Game game(server, match_selected);
  game();
}