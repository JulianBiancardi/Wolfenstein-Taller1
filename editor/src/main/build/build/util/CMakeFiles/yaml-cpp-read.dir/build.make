# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/editor/src/main

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/editor/src/main/build

# Include any dependencies generated for this target.
include build/util/CMakeFiles/yaml-cpp-read.dir/depend.make

# Include the progress variables for this target.
include build/util/CMakeFiles/yaml-cpp-read.dir/progress.make

# Include the compile flags for this target's objects.
include build/util/CMakeFiles/yaml-cpp-read.dir/flags.make

build/util/CMakeFiles/yaml-cpp-read.dir/read.cpp.o: build/util/CMakeFiles/yaml-cpp-read.dir/flags.make
build/util/CMakeFiles/yaml-cpp-read.dir/read.cpp.o: /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/common/third-party/yaml-cpp/util/read.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/julian/JULIAN/Taller1/Wolfenstein-Taller1/editor/src/main/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object build/util/CMakeFiles/yaml-cpp-read.dir/read.cpp.o"
	cd /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/editor/src/main/build/build/util && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/yaml-cpp-read.dir/read.cpp.o -c /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/common/third-party/yaml-cpp/util/read.cpp

build/util/CMakeFiles/yaml-cpp-read.dir/read.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/yaml-cpp-read.dir/read.cpp.i"
	cd /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/editor/src/main/build/build/util && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/common/third-party/yaml-cpp/util/read.cpp > CMakeFiles/yaml-cpp-read.dir/read.cpp.i

build/util/CMakeFiles/yaml-cpp-read.dir/read.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/yaml-cpp-read.dir/read.cpp.s"
	cd /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/editor/src/main/build/build/util && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/common/third-party/yaml-cpp/util/read.cpp -o CMakeFiles/yaml-cpp-read.dir/read.cpp.s

build/util/CMakeFiles/yaml-cpp-read.dir/read.cpp.o.requires:

.PHONY : build/util/CMakeFiles/yaml-cpp-read.dir/read.cpp.o.requires

build/util/CMakeFiles/yaml-cpp-read.dir/read.cpp.o.provides: build/util/CMakeFiles/yaml-cpp-read.dir/read.cpp.o.requires
	$(MAKE) -f build/util/CMakeFiles/yaml-cpp-read.dir/build.make build/util/CMakeFiles/yaml-cpp-read.dir/read.cpp.o.provides.build
.PHONY : build/util/CMakeFiles/yaml-cpp-read.dir/read.cpp.o.provides

build/util/CMakeFiles/yaml-cpp-read.dir/read.cpp.o.provides.build: build/util/CMakeFiles/yaml-cpp-read.dir/read.cpp.o


# Object files for target yaml-cpp-read
yaml__cpp__read_OBJECTS = \
"CMakeFiles/yaml-cpp-read.dir/read.cpp.o"

# External object files for target yaml-cpp-read
yaml__cpp__read_EXTERNAL_OBJECTS =

build/util/read: build/util/CMakeFiles/yaml-cpp-read.dir/read.cpp.o
build/util/read: build/util/CMakeFiles/yaml-cpp-read.dir/build.make
build/util/read: build/libyaml-cpp.a
build/util/read: build/util/CMakeFiles/yaml-cpp-read.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/julian/JULIAN/Taller1/Wolfenstein-Taller1/editor/src/main/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable read"
	cd /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/editor/src/main/build/build/util && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/yaml-cpp-read.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
build/util/CMakeFiles/yaml-cpp-read.dir/build: build/util/read

.PHONY : build/util/CMakeFiles/yaml-cpp-read.dir/build

build/util/CMakeFiles/yaml-cpp-read.dir/requires: build/util/CMakeFiles/yaml-cpp-read.dir/read.cpp.o.requires

.PHONY : build/util/CMakeFiles/yaml-cpp-read.dir/requires

build/util/CMakeFiles/yaml-cpp-read.dir/clean:
	cd /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/editor/src/main/build/build/util && $(CMAKE_COMMAND) -P CMakeFiles/yaml-cpp-read.dir/cmake_clean.cmake
.PHONY : build/util/CMakeFiles/yaml-cpp-read.dir/clean

build/util/CMakeFiles/yaml-cpp-read.dir/depend:
	cd /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/editor/src/main/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/editor/src/main /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/common/third-party/yaml-cpp/util /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/editor/src/main/build /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/editor/src/main/build/build/util /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/editor/src/main/build/build/util/CMakeFiles/yaml-cpp-read.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : build/util/CMakeFiles/yaml-cpp-read.dir/depend

