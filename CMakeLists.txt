cmake_minimum_required(VERSION 3.1)
project(wolfenstein3D)

#------------------------------------------------------------------------------
# Estándar a utilizar
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG -ggdb3 -O0 -g")
add_definitions("-DDEBUG -ggdb3 -O0 -g ")

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a;.so")
set(LUA_VERSION_STRING "5.3")
find_package(Lua 5.3)
set(CMAKE_FIND_LIBRARY_SUFFIXES ".so")
#------------------------------------------------------------------------------

#---------------------------------------------------------  QT5    ---------------------------------------------------------#
find_package(Qt5Widgets)

include_directories(${PROJECT_SOURCE_DIR}/client/src/main/launcher/include)

qt5_wrap_ui(UIS_HEADERS
  client/src/main/launcher/ui/mainwindow.ui
  client/src/main/launcher/ui/match_view.ui
  client/src/main/launcher/ui/map_view.ui
  client/src/main/launcher/ui/settings_view.ui
)
include_directories(${PROJECT_BINARY_DIR})
set(CMAKE_AUTOMOC on)
#---------------------------------------------------------  QT5    ---------------------------------------------------------#

#------------------------------------------------------------------------------
# ARCHIVOS FUENTE

FILE(GLOB_RECURSE common_src "common/src/*.cpp")
FILE(GLOB_RECURSE client_src "client/src/*.cpp")
FILE(GLOB_RECURSE server_src "server/src/*.cpp")

#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# Common
add_library(common SHARED ${common_src})

# Client
add_executable(wolfenstein3D ${client_src} ${UIS_HEADERS})
target_link_libraries(wolfenstein3D common SDL2 SDL2_image SDL2_ttf SDL2_mixer yaml-cpp Qt5::Widgets)

# Server
add_executable(server ${server_src})
target_link_libraries(server common yaml-cpp lua dl)
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# INSTALACION

# Rutas
set(BINARIES_DIRPATH "/usr/bin")
set(SHAREDLIBS_DIRPATH "/usr/lib")
set(ASSETS_DIRPATH "/var/wolfenstein3D")
set(CONFIG_DIRPATH "/etc/wolfenstein3D")

# Common
install(TARGETS common DESTINATION ${SHAREDLIBS_DIRPATH} PERMISSIONS WORLD_READ WORLD_WRITE WORLD_EXECUTE)

# Cliente
install(TARGETS wolfenstein3D DESTINATION ${BINARIES_DIRPATH} PERMISSIONS WORLD_READ WORLD_WRITE WORLD_EXECUTE WORLD_EXECUTE)

# Server
install(TARGETS server DESTINATION ${BINARIES_DIRPATH} PERMISSIONS WORLD_READ WORLD_WRITE WORLD_EXECUTE)

# Res
install(DIRECTORY ${CMAKE_SOURCE_DIR}/res DESTINATION ${ASSETS_DIRPATH} FILE_PERMISSIONS WORLD_READ WORLD_WRITE)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/common/config/ DESTINATION ${CONFIG_DIRPATH} FILE_PERMISSIONS WORLD_READ WORLD_WRITE)
