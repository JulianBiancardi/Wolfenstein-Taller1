#include <QApplication>

#include "prueba.h"

int main(int argc, char** argv) {
  // Clase que contiene el loop principal
  QApplication main_app(argc, argv);

  Prueba prueba;
  // Muestro el elemento
  prueba.show();

  // Arranca el loop de la UI
  return main_app.exec();
}