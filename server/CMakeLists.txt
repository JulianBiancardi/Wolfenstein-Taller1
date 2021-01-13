cmake_minimum_required(VERSION 3.1)
project(YamlExample)

add_subdirectory(../common/third-party/yaml-cpp build) # This is one way of referencing another
# CMake project

set(CMAKE_CXX_FLAGS "-DDEBUG -ggdb3 -O0 -g")
add_definitions("-DDEBUG -ggdb3 -O0 -g")


# Find the SDL2 library
find_package(SDL2 REQUIRED)
# Add SDL2 into include directories
include_directories(${SDL2_INCLUDE_DIR})

FILE(GLOB ServerFiles
		../common/src/main/config_loader.cpp
	src/main/map.cpp #why not?
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
	../common/src/main/object.cpp
	../common/src/main/config_loader.cpp
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
FILE(GLOB ClientTestFiles
		../client/tests/*.cpp
)

FILE(GLOB TestFiles
	#../common/tests/*.cpp Should be used
	#../common/tests/game_test/*.cpp
	#../common/tests/game_test/gun_tests.cpp
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




FILE(GLOB MapServer  src/main/map.cpp) #todo Shouldnt be here
FILE(GLOB MapClient  ../client/src/main/map.cpp) #todo Shouldnt be here



add_executable(
        server-main
        ${MainFiles}
        ${ServerFiles}
        ${CommonFiles}
        ${SDLFiles}
        ${TestFiles}
		${MainTests}
		${MapServer}

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
		#${ServerFiles}
		${CommonFiles}
		${SDLFiles}
		#${TestFiles}
		${ClientTestFiles}

		#${MainClient}

		#${MapServer}#todo should not be here.
		${MapClient}
)
target_link_libraries(
		client-main
		PRIVATE
		yaml-cpp
		${SDL2_LIBRARIES}
)



