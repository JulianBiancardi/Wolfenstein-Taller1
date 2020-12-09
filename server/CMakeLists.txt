cmake_minimum_required(VERSION 3.1)
project(YamlExample)

add_subdirectory(../common/third-party/yaml-cpp build) # This is one way of referencing another
# CMake project


# Find the SDL2 library
find_package(SDL2 REQUIRED)
# Add SDL2 into include directories
include_directories(${SDL2_INCLUDE_DIR})

FILE(GLOB ServerFiles 
	src/main/config_loader.cpp
	src/main/map.cpp
	src/main/game/*.cpp
	src/main/game/collisions/*.cpp
	src/main/game/guns/*.cpp
	#src/main/game/items/*.cpp
	src/main/game/sprites/*.cpp
	)
FILE(GLOB CommonFiles 
	../common/src/main/utils/*.cpp
	)
FILE(GLOB MainFiles
	../client/src/main/resource.cpp
        ../client/src/main/resource_manager.cpp
        )
FILE(GLOB SDLFiles
        ../client/src/main/sdl/*.cpp
)
FILE(GLOB TestFiles
	#../common/tests/*.cpp Should be used
	../common/tests/game_test/*.cpp
	../common/tests/main_tests.cpp
	../common/tests/matrix_tests.cpp
	../common/tests/point_tests.cpp
	../common/tests/ray_tests.cpp
	../common/tests/rectangle_tests.cpp
	../common/tests/resource_tests.cpp
	../common/tests/tests_setup.cpp
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
