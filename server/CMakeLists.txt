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
	#src/main/game/guns/*.cpp
	src/main/events/*.cpp
	src/main/game/objects/items/*.cpp
	src/main/game/objects/*.cpp
	)
	
FILE(GLOB CommonFiles 
	../common/src/main/data_structures/*.cpp
	../common/src/main/utils/*.cpp
)

FILE(GLOB MainFiles
	../client/src/main/resource.cpp
    ../client/src/main/resource_manager.cpp
	../client/src/main/caster.cpp
	../client/src/main/player.cpp

	../client/src/main/guns/*.cpp

	../client/src/main/casting/*.cpp
	#../client/src/main/collision.cpp
	#../client/src/main/ray_casting.cpp
	../client/src/main/client.cpp
)
FILE(GLOB SDLFiles
        ../client/src/main/sdl/*.cpp
)
FILE(GLOB TestFiles
	#../common/tests/*.cpp Should be used
	#../common/tests/game_test/*.cpp
	../common/tests/game_test/gun_tests.cpp #Should be included
	../common/tests/game_test/match_tests.cpp
	../common/tests/game_test/player_test.cpp
	../common/tests/game_test/client_mock.cpp
	#../common/tests/main_tests.cpp
	../common/tests/matrix_tests.cpp
	../common/tests/point_tests.cpp
	../common/tests/ray_tests.cpp
	../common/tests/rectangle_tests.cpp
	../common/tests/resource_tests.cpp
	../common/tests/tests_setup.cpp
	../common/tests/blocking_queue_tests.cpp
	../common/tests/protected_queue_tests.cpp
        )

FILE(GLOB MainTests  ../common/tests/main_tests.cpp) #Luego MainServer
FILE(GLOB MainClient  ../client/src/main/main.cpp) #Luego MainClient


add_executable(
        server-main
        ${MainFiles}
        ${ServerFiles}
        ${CommonFiles}
        ${SDLFiles}
        ${TestFiles}
		${MainTests}
)
# Generar el servidor
target_link_libraries(
		server-main
		PRIVATE
		yaml-cpp
		${SDL2_LIBRARIES}
)

# Generar el cliente
add_executable(
		client-main
		${MainFiles}
		${ServerFiles}
		${CommonFiles}
		${SDLFiles}
		${TestFiles}
		${MainClient}
)
target_link_libraries(
		client-main
		PRIVATE
		yaml-cpp
		${SDL2_LIBRARIES}
)



