#include <QApplication>

#include "iostream"
#include "mainwindow.h"

int main(int argc, char** argv) {
  // Clase que contiene el loop principal
  QApplication main_app(argc, argv);

  try {
    MainWindow main_window;
    main_window.show();
    main_app.exec();

  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  // Arranca el loop de la UI
  return 0;
}