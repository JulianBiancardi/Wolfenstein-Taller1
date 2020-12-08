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

        server/game/collisions/*.cpp
        server/game/sprites/*.cpp
        server/game/*.cpp

        server/config_loader.cpp
        )
FILE(GLOB CommonFiles common/*.cpp)
FILE(GLOB MainFiles
	utils/*.cpp
        map.cpp

        resource.cpp
        resource_manager.cpp
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
