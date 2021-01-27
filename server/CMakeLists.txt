cmake_minimum_required(VERSION 3.1)
project(YamlExample)

add_subdirectory(../common/third-party/yaml-cpp build) # This is one way of referencing another
# CMake project

set(CMAKE_CXX_FLAGS "-DDEBUG -ggdb3 -O0 -g")
add_definitions("-DDEBUG -ggdb3 -O0 -g ")

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a;.so")
set(LUA_VERSION_STRING "5.4")
find_package(Lua 5.4)
set(CMAKE_FIND_LIBRARY_SUFFIXES ".so")

FILE(GLOB ServerFiles
	src/main/client_manager.cpp
	src/main/client.cpp
	
	src/main/bot.cpp ##
	src/main/map.cpp # Should be everything different from main_server.cpp
	src/main/game/*.cpp
	src/main/game/*/*.cpp
	src/main/game/*/*/*.cpp

	#src/main/threads/*.cpp
		)

FILE(GLOB ServerTestsFiles
	src/tests/client_mock.cpp
	src/tests/player_test.cpp
	# src/tests/match_tests.cpp
	src/tests/bot_test.cpp
	../common/src/tests/tests_setup.cpp)

FILE(GLOB CommonFiles 
	../common/src/main/*/*.cpp
	../common/src/main/*.cpp)

FILE(GLOB ServerMain  src/main/main_server.cpp)
FILE(GLOB ServerTests  src/tests/main_tests.cpp)

add_executable(
	server_main
	${ServerMain}
	${ServerFiles}
	${CommonFiles}
)

target_link_libraries(
		server_main
		PRIVATE
		Threads::Threads
		yaml-cpp
		lua
		dl
)

add_executable(
		server_tests
		${ServerTests}
		${ServerTestsFiles}
		${ServerFiles}
		${CommonFiles}
)

target_link_libraries(
		server_tests
		PRIVATE
		Threads::Threads
		yaml-cpp
		lua
		dl
)
