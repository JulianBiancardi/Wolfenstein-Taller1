cmake_minimum_required(VERSION 3.1)
project(qt5-demo)

# This is one way of referencing another CMake project
add_subdirectory(../../../common/third-party/yaml-cpp build) 

# Busca el módulo Widgets de la biblioteca Qt5
find_package(Qt5Widgets)

# Agrego editor/include a la lista de directorios de includes
include_directories(${PROJECT_SOURCE_DIR}/view/include)
include_directories(${PROJECT_SOURCE_DIR}/model/include)


# Esta macro toma cada uno los parámetros y ejecuta *uic* sobre ellos
# La aplicacion uic genera headers con la definición de los widgets
# a partir de un archivo .ui
# Los nombres de los headers generados se guardan en la variable pasada
# como primer parámetro.
# No, no los genera con la carpeta como prefijo.
qt5_wrap_ui(UIS_HEADERS
        view/ui/option.ui
        view/ui/options_container.ui
        view/ui/celdview.ui
        view/ui/mapgrid.ui
        view/ui/mainwindow.ui
)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

# Habilito el automoc para poder hacer autoconnect de señales
set(CMAKE_AUTOMOC on)

add_executable(app
  view/src/file_manager.cpp
  view/src/celd_view.cpp
  view/src/mapgrid.cpp  
  view/src/option.cpp
  view/src/options_container.cpp
  view/src/option_selected.cpp
  view/src/itemsid.cpp
  view/src/mainwindow.cpp
  view/src/main.cpp

  model/celd.cpp
  model/map.cpp
  model/map_generator.cpp
  ${UIS_HEADERS})


# Linkea libQt5Widgets.so al ejecutable
target_link_libraries(
  app Qt5::Widgets yaml-cpp
)
