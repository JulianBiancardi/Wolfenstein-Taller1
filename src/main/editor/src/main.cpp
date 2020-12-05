#include <QApplication>

#include "iostream"
#include "itemsid.h"
#include "option.h"
#include "optionselected.h"

int main(int argc, char** argv) {
  // Clase que contiene el loop principal
  QApplication main_app(argc, argv);

  try {
    ItemsId* ids = new ItemsId();
    OptionSelected* current_option = new OptionSelected();
    Option option(nullptr, 0, ids, current_option);
    // Muestro el elemento
    option.show();
    main_app.exec();
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  // Arranca el loop de la UI
  return 0;
}