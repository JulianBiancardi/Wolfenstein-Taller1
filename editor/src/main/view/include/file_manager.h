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
  void open_file(const QString& file_path);

  /*Show the no saved message to the user*/
  void no_saved_message();

 public:
  explicit FileManager(MapGrid* map_grid);

  /*Generate a new file. Try to save the last file open if is not saved yet*/
  void new_file();

  /*Save the current file*/
  void save();

  /*Save the current file with a custom name and a custom location*/
  void save_as();

  /*Open the specified file.*/
  void open();

  /*Save all the files not saved in the close process*/
  void close();

  ~FileManager();
};

#endif /*FILE_MANAGER_H*/