# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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

#Suppress display of executed commands.
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
CMAKE_SOURCE_DIR = /home/ashton/cs381/as9

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ashton/cs381/as9/build

# Include any dependencies generated for this target.
include raylib-cpp/BufferedRaylib/CMakeFiles/buffered-raylib.dir/depend.make

# Include the progress variables for this target.
include raylib-cpp/BufferedRaylib/CMakeFiles/buffered-raylib.dir/progress.make

# Include the compile flags for this target's objects.
include raylib-cpp/BufferedRaylib/CMakeFiles/buffered-raylib.dir/flags.make

raylib-cpp/BufferedRaylib/CMakeFiles/buffered-raylib.dir/src/BufferedInput.cpp.o: raylib-cpp/BufferedRaylib/CMakeFiles/buffered-raylib.dir/flags.make
raylib-cpp/BufferedRaylib/CMakeFiles/buffered-raylib.dir/src/BufferedInput.cpp.o: ../raylib-cpp/BufferedRaylib/src/BufferedInput.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ashton/cs381/as9/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object raylib-cpp/BufferedRaylib/CMakeFiles/buffered-raylib.dir/src/BufferedInput.cpp.o"
	cd /home/ashton/cs381/as9/build/raylib-cpp/BufferedRaylib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/buffered-raylib.dir/src/BufferedInput.cpp.o -c /home/ashton/cs381/as9/raylib-cpp/BufferedRaylib/src/BufferedInput.cpp

raylib-cpp/BufferedRaylib/CMakeFiles/buffered-raylib.dir/src/BufferedInput.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/buffered-raylib.dir/src/BufferedInput.cpp.i"
	cd /home/ashton/cs381/as9/build/raylib-cpp/BufferedRaylib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ashton/cs381/as9/raylib-cpp/BufferedRaylib/src/BufferedInput.cpp > CMakeFiles/buffered-raylib.dir/src/BufferedInput.cpp.i

raylib-cpp/BufferedRaylib/CMakeFiles/buffered-raylib.dir/src/BufferedInput.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/buffered-raylib.dir/src/BufferedInput.cpp.s"
	cd /home/ashton/cs381/as9/build/raylib-cpp/BufferedRaylib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ashton/cs381/as9/raylib-cpp/BufferedRaylib/src/BufferedInput.cpp -o CMakeFiles/buffered-raylib.dir/src/BufferedInput.cpp.s

# Object files for target buffered-raylib
buffered__raylib_OBJECTS = \
"CMakeFiles/buffered-raylib.dir/src/BufferedInput.cpp.o"

# External object files for target buffered-raylib
buffered__raylib_EXTERNAL_OBJECTS =

raylib-cpp/BufferedRaylib/libbuffered-raylib.a: raylib-cpp/BufferedRaylib/CMakeFiles/buffered-raylib.dir/src/BufferedInput.cpp.o
raylib-cpp/BufferedRaylib/libbuffered-raylib.a: raylib-cpp/BufferedRaylib/CMakeFiles/buffered-raylib.dir/build.make
raylib-cpp/BufferedRaylib/libbuffered-raylib.a: raylib-cpp/BufferedRaylib/CMakeFiles/buffered-raylib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ashton/cs381/as9/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libbuffered-raylib.a"
	cd /home/ashton/cs381/as9/build/raylib-cpp/BufferedRaylib && $(CMAKE_COMMAND) -P CMakeFiles/buffered-raylib.dir/cmake_clean_target.cmake
	cd /home/ashton/cs381/as9/build/raylib-cpp/BufferedRaylib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/buffered-raylib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
raylib-cpp/BufferedRaylib/CMakeFiles/buffered-raylib.dir/build: raylib-cpp/BufferedRaylib/libbuffered-raylib.a

.PHONY : raylib-cpp/BufferedRaylib/CMakeFiles/buffered-raylib.dir/build

raylib-cpp/BufferedRaylib/CMakeFiles/buffered-raylib.dir/clean:
	cd /home/ashton/cs381/as9/build/raylib-cpp/BufferedRaylib && $(CMAKE_COMMAND) -P CMakeFiles/buffered-raylib.dir/cmake_clean.cmake
.PHONY : raylib-cpp/BufferedRaylib/CMakeFiles/buffered-raylib.dir/clean

raylib-cpp/BufferedRaylib/CMakeFiles/buffered-raylib.dir/depend:
	cd /home/ashton/cs381/as9/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ashton/cs381/as9 /home/ashton/cs381/as9/raylib-cpp/BufferedRaylib /home/ashton/cs381/as9/build /home/ashton/cs381/as9/build/raylib-cpp/BufferedRaylib /home/ashton/cs381/as9/build/raylib-cpp/BufferedRaylib/CMakeFiles/buffered-raylib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : raylib-cpp/BufferedRaylib/CMakeFiles/buffered-raylib.dir/depend

