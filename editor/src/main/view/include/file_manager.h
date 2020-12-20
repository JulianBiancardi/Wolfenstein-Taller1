#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>

#include "mapgrid.h"

class FileManager {
 private:
  MapGrid* map_grid;
  QString current_file_path;
  bool is_saved;

  void save_file(const QString& file_path);
  void no_saved_message();

 public:
  explicit FileManager(MapGrid* map_grid);

  void new_file();
  void save();
  void save_as();
  void open();
  void open_file(const QString& file_path);
  void close();

  ~FileManager();
};

#endif /*FILE_MANAGER_H*/