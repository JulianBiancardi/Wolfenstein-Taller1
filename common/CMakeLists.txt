cmake_minimum_required(VERSION 3.1)

add_subdirectory(../common/third-party/yaml-cpp build) 
# This is one way of referencing another CMake project 
# TODO Delete eventually

set(CMAKE_CXX_FLAGS "-DDEBUG -ggdb3 -O0 -g")
add_definitions("-DDEBUG -ggdb3 -O0 -g")

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

FILE(GLOB CommonFiles
	src/main/*/*.cpp
  	src/main/*.cpp)

FILE(GLOB CommonTestsFiles
  	src/tests/*.cpp
  	src/tests/*/*.cpp)

add_executable(
		common_tests
		${CommonFiles}
		${CommonTestsFiles}
)

target_link_libraries(
		common_tests
		PRIVATE
		Threads::Threads
		yaml-cpp
)