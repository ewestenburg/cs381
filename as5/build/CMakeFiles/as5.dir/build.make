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
CMAKE_SOURCE_DIR = /home/ashton/cs381/as5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ashton/cs381/as5/build

# Include any dependencies generated for this target.
include CMakeFiles/as5.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/as5.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/as5.dir/flags.make

CMakeFiles/as5.dir/src/as5.cpp.o: CMakeFiles/as5.dir/flags.make
CMakeFiles/as5.dir/src/as5.cpp.o: ../src/as5.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ashton/cs381/as5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/as5.dir/src/as5.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/as5.dir/src/as5.cpp.o -c /home/ashton/cs381/as5/src/as5.cpp

CMakeFiles/as5.dir/src/as5.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/as5.dir/src/as5.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ashton/cs381/as5/src/as5.cpp > CMakeFiles/as5.dir/src/as5.cpp.i

CMakeFiles/as5.dir/src/as5.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/as5.dir/src/as5.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ashton/cs381/as5/src/as5.cpp -o CMakeFiles/as5.dir/src/as5.cpp.s

# Object files for target as5
as5_OBJECTS = \
"CMakeFiles/as5.dir/src/as5.cpp.o"

# External object files for target as5
as5_EXTERNAL_OBJECTS =

as5: CMakeFiles/as5.dir/src/as5.cpp.o
as5: CMakeFiles/as5.dir/build.make
as5: raylib-cpp/raylib/raylib/libraylib.a
as5: /usr/lib/x86_64-linux-gnu/libOpenGL.so
as5: /usr/lib/x86_64-linux-gnu/libGLX.so
as5: /usr/lib/x86_64-linux-gnu/libGLU.so
as5: raylib-cpp/raylib/raylib/external/glfw/src/libglfw3.a
as5: /usr/lib/x86_64-linux-gnu/librt.so
as5: /usr/lib/x86_64-linux-gnu/libm.so
as5: CMakeFiles/as5.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ashton/cs381/as5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable as5"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/as5.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/as5.dir/build: as5

.PHONY : CMakeFiles/as5.dir/build

CMakeFiles/as5.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/as5.dir/cmake_clean.cmake
.PHONY : CMakeFiles/as5.dir/clean

CMakeFiles/as5.dir/depend:
	cd /home/ashton/cs381/as5/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ashton/cs381/as5 /home/ashton/cs381/as5 /home/ashton/cs381/as5/build /home/ashton/cs381/as5/build /home/ashton/cs381/as5/build/CMakeFiles/as5.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/as5.dir/depend

