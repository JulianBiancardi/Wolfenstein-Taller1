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
CMAKE_SOURCE_DIR = /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/src/main/editor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/src/main/editor/build

# Include any dependencies generated for this target.
include build/util/CMakeFiles/yaml-cpp-sandbox.dir/depend.make

# Include the progress variables for this target.
include build/util/CMakeFiles/yaml-cpp-sandbox.dir/progress.make

# Include the compile flags for this target's objects.
include build/util/CMakeFiles/yaml-cpp-sandbox.dir/flags.make

build/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.o: build/util/CMakeFiles/yaml-cpp-sandbox.dir/flags.make
build/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.o: /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/src/main/common/third-party/yaml-cpp/util/sandbox.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/julian/JULIAN/Taller1/Wolfenstein-Taller1/src/main/editor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object build/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.o"
	cd /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/src/main/editor/build/build/util && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.o -c /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/src/main/common/third-party/yaml-cpp/util/sandbox.cpp

build/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.i"
	cd /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/src/main/editor/build/build/util && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/src/main/common/third-party/yaml-cpp/util/sandbox.cpp > CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.i

build/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.s"
	cd /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/src/main/editor/build/build/util && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/src/main/common/third-party/yaml-cpp/util/sandbox.cpp -o CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.s

build/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.o.requires:

.PHONY : build/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.o.requires

build/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.o.provides: build/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.o.requires
	$(MAKE) -f build/util/CMakeFiles/yaml-cpp-sandbox.dir/build.make build/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.o.provides.build
.PHONY : build/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.o.provides

build/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.o.provides.build: build/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.o


# Object files for target yaml-cpp-sandbox
yaml__cpp__sandbox_OBJECTS = \
"CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.o"

# External object files for target yaml-cpp-sandbox
yaml__cpp__sandbox_EXTERNAL_OBJECTS =

build/util/sandbox: build/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.o
build/util/sandbox: build/util/CMakeFiles/yaml-cpp-sandbox.dir/build.make
build/util/sandbox: build/libyaml-cpp.a
build/util/sandbox: build/util/CMakeFiles/yaml-cpp-sandbox.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/julian/JULIAN/Taller1/Wolfenstein-Taller1/src/main/editor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sandbox"
	cd /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/src/main/editor/build/build/util && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/yaml-cpp-sandbox.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
build/util/CMakeFiles/yaml-cpp-sandbox.dir/build: build/util/sandbox

.PHONY : build/util/CMakeFiles/yaml-cpp-sandbox.dir/build

build/util/CMakeFiles/yaml-cpp-sandbox.dir/requires: build/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.o.requires

.PHONY : build/util/CMakeFiles/yaml-cpp-sandbox.dir/requires

build/util/CMakeFiles/yaml-cpp-sandbox.dir/clean:
	cd /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/src/main/editor/build/build/util && $(CMAKE_COMMAND) -P CMakeFiles/yaml-cpp-sandbox.dir/cmake_clean.cmake
.PHONY : build/util/CMakeFiles/yaml-cpp-sandbox.dir/clean

build/util/CMakeFiles/yaml-cpp-sandbox.dir/depend:
	cd /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/src/main/editor/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/src/main/editor /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/src/main/common/third-party/yaml-cpp/util /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/src/main/editor/build /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/src/main/editor/build/build/util /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/src/main/editor/build/build/util/CMakeFiles/yaml-cpp-sandbox.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : build/util/CMakeFiles/yaml-cpp-sandbox.dir/depend

