# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/santiagoczop/Taller/tps/tp4/server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/santiagoczop/Taller/tps/tp4/server/build

# Utility rule file for ContinuousTest.

# Include the progress variables for this target.
include build/CMakeFiles/ContinuousTest.dir/progress.make

build/CMakeFiles/ContinuousTest:
	cd /home/santiagoczop/Taller/tps/tp4/server/build/build && /usr/bin/ctest -D ContinuousTest

ContinuousTest: build/CMakeFiles/ContinuousTest
ContinuousTest: build/CMakeFiles/ContinuousTest.dir/build.make

.PHONY : ContinuousTest

# Rule to build all files generated by this target.
build/CMakeFiles/ContinuousTest.dir/build: ContinuousTest

.PHONY : build/CMakeFiles/ContinuousTest.dir/build

build/CMakeFiles/ContinuousTest.dir/clean:
	cd /home/santiagoczop/Taller/tps/tp4/server/build/build && $(CMAKE_COMMAND) -P CMakeFiles/ContinuousTest.dir/cmake_clean.cmake
.PHONY : build/CMakeFiles/ContinuousTest.dir/clean

build/CMakeFiles/ContinuousTest.dir/depend:
	cd /home/santiagoczop/Taller/tps/tp4/server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/santiagoczop/Taller/tps/tp4/server /home/santiagoczop/Taller/tps/tp4/common/third-party/yaml-cpp /home/santiagoczop/Taller/tps/tp4/server/build /home/santiagoczop/Taller/tps/tp4/server/build/build /home/santiagoczop/Taller/tps/tp4/server/build/build/CMakeFiles/ContinuousTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : build/CMakeFiles/ContinuousTest.dir/depend

