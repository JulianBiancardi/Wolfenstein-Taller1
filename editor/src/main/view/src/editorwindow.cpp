#include "editorwindow.h"

#include "../../model/include/map_generator.h"
#include "iostream"
#include "moc_editorwindow.cpp"

#define WINDOW_TITLE "Wolfenstein Editor"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  ui.setupUi(this);
  setWindowTitle(WINDOW_TITLE);

  ItemsId* ids = new ItemsId();
  OptionSelected* current_option = new OptionSelected();

  // ui.OptionsContainerWidget->addOptions(ids, current_option);

  ui.MapGridWidget->init(ids, current_option);
  ui.ToolsWidget->init(ids, current_option, ui.MapGridWidget);
  file_manager = new FileManager(ui.MapGridWidget);
}

void MainWindow::on_actionNew_File_triggered() { file_manager->new_file(); }
void MainWindow::on_actionOpen_File_triggered() { file_manager->open(); }
void MainWindow::on_actionSave_triggered() { file_manager->save(); }
void MainWindow::on_actionSave_As_triggered() { file_manager->save_as(); }
void MainWindow::on_actionExit_triggered() { file_manager->close(); }

void MainWindow::closeEvent(QCloseEvent* event) {
  event->ignore();
  file_manager->close();
  // event->accept();
}

void MainWindow::on_actionUndo_triggered() { ui.MapGridWidget->undo(); }
void MainWindow::on_actionRedo_triggered() { ui.MapGridWidget->redo(); }

MainWindow::~MainWindow() { delete file_manager; }