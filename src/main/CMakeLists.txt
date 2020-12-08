cmake_minimum_required(VERSION 3.1)
project(YamlExample)

add_subdirectory(common/third-party/yaml-cpp) # This is one way of referencing another
# CMake project


# Find the SDL2 library
find_package(SDL2 REQUIRED)
# Add SDL2 into include directories
include_directories(${SDL2_INCLUDE_DIR})



FILE(GLOB ServerFiles
        server/game/guns/*.cpp

        server/game/collisions/circle_mask.cpp
        server/game/player.cpp
        server/game/moveable.cpp

        server/config_loader.cpp
        )
FILE(GLOB CommonFiles common/*.cpp)
FILE(GLOB MainFiles
        point.cpp
        ray.cpp

        matrix.cpp
        map.cpp

        rectangle.cpp
        resource.cpp
<<<<<<< HEAD
        resource_manager.cpp
=======

>>>>>>> d54385d950ab6e4b25f29ec915ef813a4f6cd066
        )
FILE(GLOB SDLFiles
        sdl/*.cpp
)
FILE(GLOB TestFiles
        ../tests/game_test/gun_tests.cpp
        ../tests/game_test/player_test.cpp

        #../tests/main_tests.cpp
        #../tests/matrix_tests.cpp
        #../tests/point_tests.cpp
        #../tests/ray_tests.cpp
        #../tests/rectangle_tests.cpp
        #../tests/tests_setup.cpp

        ../tests/*.cpp
        )
add_executable(
        main
        ${MainFiles}
        ${ServerFiles}
        ${CommonFiles}
        ${SDLFiles}
        ${TestFiles}
)

target_link_libraries(
        main
        PRIVATE
        yaml-cpp  # This is the "target" exposed by yaml-cpp's CMakeLists.txt file
        ${SDL2_LIBRARIES}
)
