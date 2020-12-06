cmake_minimum_required(VERSION 3.1)
project(YamlExample)

add_subdirectory(common/third-party/yaml-cpp) # This is one way of referencing another
# CMake project

FILE(GLOB ServerFiles
        server/game/guns/*.cpp

        server/game/player.cpp
        server/game/map.cpp

        server/config_loader.cpp
        )
FILE(GLOB CommonFiles common/*.cpp)
FILE(GLOB MainFiles
        point.cpp
        ray.cpp
        )
FILE(GLOB TestFiles
        ../tests/game_test/gun_tests.cpp
        ../tests/*.cpp
        )
add_executable(
        server
        ${MainFiles}
        ${ServerFiles}
        ${CommonFiles}
        ${TestFiles}
)

target_link_libraries(
        server
        PRIVATE
        yaml-cpp  # This is the "target" exposed by yaml-cpp's CMakeLists.txt file
)