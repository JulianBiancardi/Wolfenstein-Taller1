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
CMAKE_SOURCE_DIR = /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/client/build

# Utility rule file for NightlyMemoryCheck.

# Include the progress variables for this target.
include build/CMakeFiles/NightlyMemoryCheck.dir/progress.make

build/CMakeFiles/NightlyMemoryCheck:
	cd /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/client/build/build && /usr/bin/ctest -D NightlyMemoryCheck

NightlyMemoryCheck: build/CMakeFiles/NightlyMemoryCheck
NightlyMemoryCheck: build/CMakeFiles/NightlyMemoryCheck.dir/build.make

.PHONY : NightlyMemoryCheck

# Rule to build all files generated by this target.
build/CMakeFiles/NightlyMemoryCheck.dir/build: NightlyMemoryCheck

.PHONY : build/CMakeFiles/NightlyMemoryCheck.dir/build

build/CMakeFiles/NightlyMemoryCheck.dir/clean:
	cd /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/client/build/build && $(CMAKE_COMMAND) -P CMakeFiles/NightlyMemoryCheck.dir/cmake_clean.cmake
.PHONY : build/CMakeFiles/NightlyMemoryCheck.dir/clean

build/CMakeFiles/NightlyMemoryCheck.dir/depend:
	cd /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/client/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/client /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/common/third-party/yaml-cpp /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/client/build /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/client/build/build /home/julian/JULIAN/Taller1/Wolfenstein-Taller1/client/build/build/CMakeFiles/NightlyMemoryCheck.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : build/CMakeFiles/NightlyMemoryCheck.dir/depend

