#include "iostream"
#include "map.h"

int main(int args, char** argv) {
  Map map_editor(5, 5);  // Fill the map by default id

  map_editor.put(7, 1, 3);  // Put the id = 3 in the (0,3)
  map_editor.put(0, 2, 3);  // Put the id = 3 in the (0,3)
  map_editor.put(0, 3, 3);  // Put the id = 3 in the (0,3)
  map_editor.clear(0, 1);   // clear the celd especified
  map_editor.clear_all();   // Clear all the map, put default id

  return 0;
}