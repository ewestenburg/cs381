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
CMAKE_SOURCE_DIR = /home/ashton/cs381/as6

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ashton/cs381/as6/build

# Include any dependencies generated for this target.
include CMakeFiles/as6.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/as6.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/as6.dir/flags.make

CMakeFiles/as6.dir/src/as6.cpp.o: CMakeFiles/as6.dir/flags.make
CMakeFiles/as6.dir/src/as6.cpp.o: ../src/as6.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ashton/cs381/as6/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/as6.dir/src/as6.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/as6.dir/src/as6.cpp.o -c /home/ashton/cs381/as6/src/as6.cpp

CMakeFiles/as6.dir/src/as6.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/as6.dir/src/as6.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ashton/cs381/as6/src/as6.cpp > CMakeFiles/as6.dir/src/as6.cpp.i

CMakeFiles/as6.dir/src/as6.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/as6.dir/src/as6.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ashton/cs381/as6/src/as6.cpp -o CMakeFiles/as6.dir/src/as6.cpp.s

CMakeFiles/as6.dir/src/skybox.cpp.o: CMakeFiles/as6.dir/flags.make
CMakeFiles/as6.dir/src/skybox.cpp.o: ../src/skybox.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ashton/cs381/as6/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/as6.dir/src/skybox.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/as6.dir/src/skybox.cpp.o -c /home/ashton/cs381/as6/src/skybox.cpp

CMakeFiles/as6.dir/src/skybox.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/as6.dir/src/skybox.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ashton/cs381/as6/src/skybox.cpp > CMakeFiles/as6.dir/src/skybox.cpp.i

CMakeFiles/as6.dir/src/skybox.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/as6.dir/src/skybox.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ashton/cs381/as6/src/skybox.cpp -o CMakeFiles/as6.dir/src/skybox.cpp.s

# Object files for target as6
as6_OBJECTS = \
"CMakeFiles/as6.dir/src/as6.cpp.o" \
"CMakeFiles/as6.dir/src/skybox.cpp.o"

# External object files for target as6
as6_EXTERNAL_OBJECTS =

as6: CMakeFiles/as6.dir/src/as6.cpp.o
as6: CMakeFiles/as6.dir/src/skybox.cpp.o
as6: CMakeFiles/as6.dir/build.make
as6: raylib-cpp/raylib/raylib/libraylib.a
as6: /usr/lib/x86_64-linux-gnu/libOpenGL.so
as6: /usr/lib/x86_64-linux-gnu/libGLX.so
as6: /usr/lib/x86_64-linux-gnu/libGLU.so
as6: raylib-cpp/raylib/raylib/external/glfw/src/libglfw3.a
as6: /usr/lib/x86_64-linux-gnu/librt.so
as6: /usr/lib/x86_64-linux-gnu/libm.so
as6: CMakeFiles/as6.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ashton/cs381/as6/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable as6"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/as6.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/as6.dir/build: as6

.PHONY : CMakeFiles/as6.dir/build

CMakeFiles/as6.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/as6.dir/cmake_clean.cmake
.PHONY : CMakeFiles/as6.dir/clean

CMakeFiles/as6.dir/depend:
	cd /home/ashton/cs381/as6/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ashton/cs381/as6 /home/ashton/cs381/as6 /home/ashton/cs381/as6/build /home/ashton/cs381/as6/build /home/ashton/cs381/as6/build/CMakeFiles/as6.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/as6.dir/depend

