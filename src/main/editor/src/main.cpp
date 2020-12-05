#include <QApplication>

#include "iostream"
#include "itemsid.h"
#include "option_selected.h"
#include "options_container.h"

int main(int argc, char** argv) {
  // Clase que contiene el loop principal
  QApplication main_app(argc, argv);

  try {
    ItemsId ids;
    OptionSelected current_option;
    OptionsContainer options_container(nullptr, 2, &ids, &current_option);
    // Muestro el elemento
    options_container.show();
    main_app.exec();
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  // Arranca el loop de la UI
  return 0;
}