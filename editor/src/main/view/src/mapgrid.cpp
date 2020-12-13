#include "mapgrid.h"

#include <QtCore/QDebug>     //TODO delete
#include <QtCore/QMimeData>  //Data for drag and drop system

#include "../../model/include/map_generator.h"
#include "celd_view.h"
#include "iostream"
#include "moc_mapgrid.cpp"

#define INVALID_ID -1

//-----------------------------------------------------------------------------
MapGrid::MapGrid(QWidget* parent, Map* map, ItemsId* ids,
                 OptionSelected* current_option)
    : QWidget(parent),
      map(map),
      ids(ids),
      current_option(current_option),
      is_saved(true) {
  this->ui.setupUi(this);
  this->setAcceptDrops(true);
  generateCelds();
}

MapGrid::~MapGrid() {}

void MapGrid::generateCelds() {
  QGridLayout* gridlayout = new QGridLayout();
  gridlayout->setSpacing(0);
  for (size_t row = 0; row < this->map->row_count(); row++) {
    for (size_t column = 0; column < this->map->column_count(); column++) {
      CeldView* celd_view = new CeldView(this, this->map->at(row, column),
                                         this->ids, this->current_option);
      gridlayout->addWidget(celd_view, row, column);
    }
  }
  this->ui.scrollContent->setLayout(gridlayout);
}

void MapGrid::clear() { this->map->clear_all(); }
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
*/

void MapGrid::open_map(const std::string& file_path) {
  if (file_path.empty()) {
    return;
  }

  MapGenerator map_generator;
  map_generator.generate_map(file_path, this->map);
}

void MapGrid::generate_yamlfile(const std::string& file_path) {
  MapGenerator file_generator;
  file_generator.generate_yamlfile(file_path, this->map);
}

void MapGrid::dragEnterEvent(QDragEnterEvent* event) {
  std::cout << "Drag enter event" << std::endl;
  event->acceptProposedAction();
}

void MapGrid::dropEvent(QDropEvent* event) {
  qDebug() << "dropEvent" << event;

  const QMimeData* mimeData = event->mimeData();

  // check for our needed mime type, here a file or a list of files
  if (mimeData->hasUrls()) {
    // QStringList pathList;
    QList<QUrl> urlList = mimeData->urls();

    /*
        // extract the local paths of the files
        for (int i = 0; i < urlList.size() && i < 32; + i) {
          pathList.append(urlList.at(i).toLocalFile());
        }*/

    // extract only the first file
    QString file_path = urlList.first().toLocalFile();

    // call a function to open the files
    // openFiles(pathList);
    this->open_map(file_path.toStdString());
  }
}

void MapGrid::set_saved(bool status) {
  this->is_saved = status;
  std::cout << this->is_saved << std::endl;
}

bool MapGrid::saved() const {
  std::cout << this->is_saved << std::endl;
  return this->is_saved;
}
