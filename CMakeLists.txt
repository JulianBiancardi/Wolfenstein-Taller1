cmake_minimum_required(VERSION 3.1)
project(YamlExample)

add_subdirectory(common/third-party/yaml-cpp) # This is one way of referencing another
# CMake project


FILE(GLOB ServerFiles server/*.cpp)
FILE(GLOB CommonFiles common/*.cpp)

add_executable(
        server
#        main.cpp
#        file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "server/*.cpp")
#        file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "common/*.cpp")

        ${ServerFiles}
        ${CommonFiles}


        #server/*.cpp
        #common/*.cpp

)

target_link_libraries(
        server
        PRIVATE
        yaml-cpp  # This is the "target" exposed by yaml-cpp's CMakeLists.txt file
)