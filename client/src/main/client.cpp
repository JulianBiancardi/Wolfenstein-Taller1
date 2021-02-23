#include "client.h"

#include <QtWidgets/QApplication>
#include <exception>

#include "../../../common/src/main/config_loader.h"
#include "game/game.h"
#include "launcher/include/mainwindow.h"
#include "launcher/include/match.h"
#include "launcher/include/settings.h"
#include "server.h"

Client::Client() {}

Client::~Client() {}

void Client::run_client(int argc, char** argv) {
  Server server;
  Settings settings;
  Match match_selected;

  while (true) {
    try {
      QApplication launcher_app(argc, argv);
      MainWindow launcher(nullptr, &server, &settings, &match_selected);
      launcher.show();
      launcher.update();
      launcher_app.exec();

    } catch (const std::exception& e) {
      std::cerr << e.what() << '\n';
    }

    if (!match_selected.is_valid()) {
      break;
    }

    Game game(server, settings, match_selected);
    game();
  }
}