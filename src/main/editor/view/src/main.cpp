#include <QtWidgets/QApplication>

#include "../model/include/map.h"
#include "iostream"
#include "itemsid.h"
#include "mapgrid.h"
#include "option_selected.h"

int main(int argc, char** argv) {
  // Clase que contiene el loop principal
  QApplication main_app(argc, argv);

  try {
    /*
    MainWindow main_window;
    main_window.show();*/

    ItemsId ids;
    OptionSelected current_option;

    Map map(3, 3);
    MapGrid map_grid(nullptr, map, ids, current_option);
    map_grid.show();

    // Arranca el loop de la UI
    main_app.exec();

  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  return 0;
}