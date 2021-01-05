#include <QtWidgets/QApplication>

#include "../model/include/map.h"
#include "iostream"
#include "mainwindow.h"

int main(int argc, char** argv) {
  // Clase que contiene el loop principal
  QApplication main_app(argc, argv);

  try {
    MainWindow main_window(nullptr);
    main_window.show();
    // Arranca el loop de la UI
    main_app.exec();

  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
  return 0;
}