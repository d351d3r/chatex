# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_SOURCE_DIR = /mnt/c/Users/stdmatrix/Desktop/chatex

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/stdmatrix/Desktop/chatex/cmake-build-debug

# Include any dependencies generated for this target.
include src/server/CMakeFiles/server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/server/CMakeFiles/server.dir/compiler_depend.make

# Include the progress variables for this target.
include src/server/CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include src/server/CMakeFiles/server.dir/flags.make

src/server/CMakeFiles/server.dir/Server.cpp.o: src/server/CMakeFiles/server.dir/flags.make
src/server/CMakeFiles/server.dir/Server.cpp.o: ../src/server/Server.cpp
src/server/CMakeFiles/server.dir/Server.cpp.o: src/server/CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/stdmatrix/Desktop/chatex/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/server/CMakeFiles/server.dir/Server.cpp.o"
	cd /mnt/c/Users/stdmatrix/Desktop/chatex/cmake-build-debug/src/server && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/server/CMakeFiles/server.dir/Server.cpp.o -MF CMakeFiles/server.dir/Server.cpp.o.d -o CMakeFiles/server.dir/Server.cpp.o -c /mnt/c/Users/stdmatrix/Desktop/chatex/src/server/Server.cpp

src/server/CMakeFiles/server.dir/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/Server.cpp.i"
	cd /mnt/c/Users/stdmatrix/Desktop/chatex/cmake-build-debug/src/server && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/stdmatrix/Desktop/chatex/src/server/Server.cpp > CMakeFiles/server.dir/Server.cpp.i

src/server/CMakeFiles/server.dir/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/Server.cpp.s"
	cd /mnt/c/Users/stdmatrix/Desktop/chatex/cmake-build-debug/src/server && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/stdmatrix/Desktop/chatex/src/server/Server.cpp -o CMakeFiles/server.dir/Server.cpp.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/Server.cpp.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

src/server/libserver.a: src/server/CMakeFiles/server.dir/Server.cpp.o
src/server/libserver.a: src/server/CMakeFiles/server.dir/build.make
src/server/libserver.a: src/server/CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/stdmatrix/Desktop/chatex/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libserver.a"
	cd /mnt/c/Users/stdmatrix/Desktop/chatex/cmake-build-debug/src/server && $(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean_target.cmake
	cd /mnt/c/Users/stdmatrix/Desktop/chatex/cmake-build-debug/src/server && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/server/CMakeFiles/server.dir/build: src/server/libserver.a
.PHONY : src/server/CMakeFiles/server.dir/build

src/server/CMakeFiles/server.dir/clean:
	cd /mnt/c/Users/stdmatrix/Desktop/chatex/cmake-build-debug/src/server && $(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : src/server/CMakeFiles/server.dir/clean

src/server/CMakeFiles/server.dir/depend:
	cd /mnt/c/Users/stdmatrix/Desktop/chatex/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/stdmatrix/Desktop/chatex /mnt/c/Users/stdmatrix/Desktop/chatex/src/server /mnt/c/Users/stdmatrix/Desktop/chatex/cmake-build-debug /mnt/c/Users/stdmatrix/Desktop/chatex/cmake-build-debug/src/server /mnt/c/Users/stdmatrix/Desktop/chatex/cmake-build-debug/src/server/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/server/CMakeFiles/server.dir/depend

