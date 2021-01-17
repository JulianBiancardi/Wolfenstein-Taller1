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

FILE(GLOB ClientFiles
  src/main/*.cpp
  src/main/casting/*.cpp
  src/main/guns/*.cpp
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

  ../common/src/main/object.cpp
  ../common/src/main/identifiable.cpp
	../common/src/main/config_loader.cpp
)

# FIXME Once the files work, delete their line
list(REMOVE_ITEM ClientFiles "/home/santiagoczop/Taller/tps/tp4/client/src/main/stage.cpp")
list(REMOVE_ITEM ClientFiles "/home/santiagoczop/Taller/tps/tp4/client/src/main/main.cpp")
list(REMOVE_ITEM ClientTestsFiles "/home/santiagoczop/Taller/tps/tp4/client/src/tests/gun_tests.cpp")
list(REMOVE_ITEM ClientTestsFiles "/home/santiagoczop/Taller/tps/tp4/client/src/tests/resource_manager_tests.cpp")

add_executable(
  client_tests
  ${ClientFiles}
  ${ClientTestsFiles}
  ${CommonFiles}
)

target_link_libraries(
  client_tests
  PRIVATE
  yaml-cpp
  Threads::Threads
  ${SDL2_LIBRARIES}
)