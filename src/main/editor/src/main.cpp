#include <QApplication>

#include "option.h"

int main(int argc, char** argv) {
  // Clase que contiene el loop principal
  QApplication main_app(argc, argv);

  Option option;
  // Muestro el elemento
  option.show();

  // Arranca el loop de la UI
  return main_app.exec();
}