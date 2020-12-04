#include "prueba.h"

// Cargo el archivo generado por uic, leer el CMakelist.txt para mas info
#include "ui_prueba.h"

Prueba::Prueba(QWidget* parent) : QWidget(parent) {
  // Instancio la configuracion generada por el designer y uic //ACORDASE DE
  // CAMBIAAR EL NOMBRE DEL OBJETO FORM EN QT DESIGNER
  Ui::Prueba prueba;
  // Configuro este widget para use esa configuracion
  prueba.setupUi(this);
}

Prueba::~Prueba() {}