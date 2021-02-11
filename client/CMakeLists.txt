cmake_minimum_required(VERSION 3.1)
project(Client)

add_subdirectory(../common/third-party/yaml-cpp build) 
# This is one way of referencing another CMake project 
# TODO Delete eventually

set(CMAKE_CXX_FLAGS "-DDEBUG -ggdb3 -O0 -g")
add_definitions("-DDEBUG -ggdb3 -O0 -g")

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

# Find the SDL2 library
find_package(SDL2 REQUIRED)
# Add SDL2 into include directories
include_directories(${SDL2_INCLUDE_DIR})

#---------------------------------------------------------  QT5    ---------------------------------------------------------#
find_package(Qt5Widgets)

include_directories(${PROJECT_SOURCE_DIR}/src/main/launcher/include)

qt5_wrap_ui(UIS_HEADERS
  src/main/launcher/ui/mainwindow.ui
  src/main/launcher/ui/match_view.ui
  src/main/launcher/ui/map_view.ui
)
include_directories(${PROJECT_BINARY_DIR})
set(CMAKE_AUTOMOC on)

FILE(GLOB QtViewFiles
  src/main/launcher/model/*.cpp
  src/main/launcher/view/*.cpp
)
#---------------------------------------------------------  QT5    ---------------------------------------------------------#

FILE(GLOB ClientFiles
  src/main/*.cpp
  src/main/casters/*.cpp
  src/main/casting/*.cpp
  src/main/guns/*.cpp
  src/main/guns/*/*.cpp
  src/main/hud/*.cpp
  src/main/packet_handlers/*.cpp
  src/main/sdl/*.cpp
  src/main/threads/*.cpp
)

FILE(GLOB ClientTestsFiles
  src/tests/*.cpp
)

FILE(GLOB CommonFiles
  ../common/src/main/collisions/*.cpp
	../common/src/main/data_structures/*.cpp
  ../common/src/main/socket/*.cpp
  ../common/src/main/threads/*.cpp
	../common/src/main/utils/*.cpp
	../common/src/main/packets/*.cpp
	../common/src/main/exceptions/*.cpp

  ../common/src/main/object.cpp
  ../common/src/main/identifiable.cpp
	../common/src/main/config_loader.cpp
  ../common/src/main/Iobservable.cpp
  ../common/src/main/Iobserver.cpp
)

# FIXME Once the files work, delete their line
list(REMOVE_ITEM ClientFiles "/home/julian/JULIAN/Taller1/Wolfenstein-Taller1/client/src/main/stage.cpp")
list(REMOVE_ITEM ClientTestsFiles "/home/julian/JULIAN/Taller1/Wolfenstein-Taller1/client/src/tests/gun_tests.cpp")
list(REMOVE_ITEM ClientTestsFiles "/home/julian/JULIAN/Taller1/Wolfenstein-Taller1/client/src/tests/resource_manager_tests.cpp")

add_executable(
  client
  ${ClientFiles}
  ${QtViewFiles}
  #${ClientTestsFiles}
  ${CommonFiles}
  ${UIS_HEADERS}
)

target_link_libraries(
  client
  PRIVATE
  SDL2
  SDL2_image
  SDL2_ttf
  SDL2_mixer
  dl
  Qt5::Widgets
  yaml-cpp
  Threads::Threads
  ${SDL2_LIBRARIES}
)
