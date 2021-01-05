#include "include/map.h"
#include "iostream"

int main(int args, char** argv) {
  Map map_editor(5, 5);  // Fill the map by default id

  map_editor.put(0, 0, 3);  // Put the id = 3 in the (0,3)
  map_editor.put(0, 1, 3);  // Put the id = 3 in the (0,3)
  map_editor.put(1, 0, 3);  // Put the id = 3 in the (0,3)
  map_editor.print();

  // map_editor.insert_rowup();
  // map_editor.remove_rowup();
  map_editor.remove_rowdown();
  map_editor.remove_rowdown();
  map_editor.remove_rowdown();
  map_editor.remove_rowdown();
  map_editor.remove_rowdown();
  map_editor.remove_rowdown();
  map_editor.put(0, 0, 1);  // Put the id = 1 in the (0,0)
  std::cout << std::endl;
  std::cout << std::endl;
  map_editor.print();

  map_editor.clear(0, 0);  // clear the celd especified
  std::cout << std::endl;
  std::cout << std::endl;
  map_editor.print();
  return 0;
}