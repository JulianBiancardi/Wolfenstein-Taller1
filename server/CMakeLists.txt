cmake_minimum_required(VERSION 3.1)
project(YamlExample)

add_subdirectory(../common/third-party/yaml-cpp build) # This is one way of referencing another
# CMake project

set(CMAKE_CXX_FLAGS "-DDEBUG -ggdb3 -O0 -g")
add_definitions("-DDEBUG -ggdb3 -O0 -g")

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

FILE(GLOB ServerFiles
	src/main/*.cpp
	src/main/events/*.cpp
	src/main/game/*.cpp
	src/main/game/*/*.cpp
	src/main/game/*/*/*.cpp
	src/main/threads/*.cpp
	)
	
FILE(GLOB CommonFiles 
	../common/src/main/*/*.cpp
	../common/src/main/*.cpp
		)

# Esto para que esta?
FILE(GLOB MainTests  ../common/tests/main_tests.cpp) #Luego MainServer
FILE(GLOB MainClient  ../client/src/main/main.cpp) #Luego MainClient

add_executable(
	server_tests
	${ServerFiles}
	${CommonFiles}
)

#add_executable(

        #server-main
        #${MainFiles}
        #${ServerFiles}
        #${CommonFiles}
        #${TestFiles}
		#${MainTests}
#)

# Generar el servidor
target_link_libraries(
		server_tests
		PRIVATE
		Threads::Threads
		yaml-cpp
)
