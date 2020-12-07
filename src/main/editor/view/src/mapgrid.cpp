#include "mapgrid.h"

#include <fstream>

#include "celd_view.h"
#include "iostream"
#include "moc_mapgrid.cpp"
#include "yaml-cpp/yaml.h"

#define INVALID_ID -1

//-----------------------------------------------------------------------------
MapGrid::MapGrid(QWidget* parent, Map& map, ItemsId& ids,
                 OptionSelected& current_option)
    : QWidget(parent), map(map), ids(ids), current_option(current_option) {
  this->ui.setupUi(this);
  generateCelds();
}

MapGrid::~MapGrid() {}

void MapGrid::generateCelds() {
  QGridLayout* gridlayout = new QGridLayout();
  gridlayout->setSpacing(0);
  for (size_t row = 0; row < this->map.row_count(); row++) {
    for (size_t column = 0; column < this->map.column_count(); column++) {
      CeldView* celd_view = new CeldView(this, this->map.at(row, column),
                                         this->ids, this->current_option);
      gridlayout->addWidget(celd_view, row, column);
    }
  }
  this->ui.scrollContent->setLayout(gridlayout);
}

void MapGrid::clear() {}
/*
void MapGrid::resize(size_t new_rows, size_t new_columns) {
  if (this->rows == new_rows && this->columns == new_columns) {
    return;
  }

  QGridLayout* gridlayout = ((QGridLayout*)this->ui.scrollContent->layout());
  QGridLayout* newgridlayout = new QGridLayout();
  newgridlayout->setSpacing(0);
  for (size_t row = 0; row < new_rows; row++) {
    for (size_t column = 0; column < new_columns; column++) {
      QWidget* widget = gridlayout->itemAtPosition(row, column)->widget();
      if (widget != nullptr) {
        newgridlayout->addWidget(widget, row, column);
      } else {
        CeldView* celd = new CeldView(this, this->ids, this->current_option);
        newgridlayout->addWidget(celd, row, column);
      }
    }
  }
  delete (this->ui.scrollContent->layout());
  this->ui.scrollContent->setLayout(newgridlayout);
  this->rows = new_rows;
  this->columns = new_columns;
}

void MapGrid::generate_yamlfile() {
  std::cout << "generating file" << std::endl;
  YAML::Emitter out;
  out << YAML::BeginMap;
  out << YAML::Key << "width";
  out << YAML::Value << this->columns;
  out << YAML::Key << "height";
  out << YAML::Value << this->rows;
  out << YAML::Key << "objects";
  out << YAML::Value << YAML::BeginSeq;
  QGridLayout* gridlayout = (QGridLayout*)this->ui.scrollContent->layout();
  for (size_t row = 0; row < this->rows; row++) {
    for (size_t column = 0; column < this->columns; column++) {
      CeldView* celd_view =
          (CeldView*)gridlayout->itemAtPosition(row, column)->widget();
      if (celd_view != NULL && celd_view->get_id() != INVALID_ID) {
        out << YAML::BeginMap;
        out << YAML::Key << "id";
        out << YAML::Value << celd->getid();
        out << YAML::Key << "x_position";
        out << YAML::Value << column;
        out << YAML::Key << "y_position";
        out << YAML::Value << row;
        out << YAML::EndMap;
      }
    }
  }

  out << YAML::EndSeq;
  out << YAML::EndMap;
  std::cout << out.c_str() << std::endl;
  std::ofstream fout("new_map.yaml");
  fout << out.c_str();
}*/
