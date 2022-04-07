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
include client/CMakeFiles/talker_helper.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include client/CMakeFiles/talker_helper.dir/compiler_depend.make

# Include the progress variables for this target.
include client/CMakeFiles/talker_helper.dir/progress.make

# Include the compile flags for this target's objects.
include client/CMakeFiles/talker_helper.dir/flags.make

client/CMakeFiles/talker_helper.dir/talk_helper.cpp.o: client/CMakeFiles/talker_helper.dir/flags.make
client/CMakeFiles/talker_helper.dir/talk_helper.cpp.o: ../client/talk_helper.cpp
client/CMakeFiles/talker_helper.dir/talk_helper.cpp.o: client/CMakeFiles/talker_helper.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/stdmatrix/Desktop/chatex/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object client/CMakeFiles/talker_helper.dir/talk_helper.cpp.o"
	cd /mnt/c/Users/stdmatrix/Desktop/chatex/cmake-build-debug/client && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT client/CMakeFiles/talker_helper.dir/talk_helper.cpp.o -MF CMakeFiles/talker_helper.dir/talk_helper.cpp.o.d -o CMakeFiles/talker_helper.dir/talk_helper.cpp.o -c /mnt/c/Users/stdmatrix/Desktop/chatex/client/talk_helper.cpp

client/CMakeFiles/talker_helper.dir/talk_helper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/talker_helper.dir/talk_helper.cpp.i"
	cd /mnt/c/Users/stdmatrix/Desktop/chatex/cmake-build-debug/client && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/stdmatrix/Desktop/chatex/client/talk_helper.cpp > CMakeFiles/talker_helper.dir/talk_helper.cpp.i

client/CMakeFiles/talker_helper.dir/talk_helper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/talker_helper.dir/talk_helper.cpp.s"
	cd /mnt/c/Users/stdmatrix/Desktop/chatex/cmake-build-debug/client && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/stdmatrix/Desktop/chatex/client/talk_helper.cpp -o CMakeFiles/talker_helper.dir/talk_helper.cpp.s

# Object files for target talker_helper
talker_helper_OBJECTS = \
"CMakeFiles/talker_helper.dir/talk_helper.cpp.o"

# External object files for target talker_helper
talker_helper_EXTERNAL_OBJECTS =

client/libtalker_helper.a: client/CMakeFiles/talker_helper.dir/talk_helper.cpp.o
client/libtalker_helper.a: client/CMakeFiles/talker_helper.dir/build.make
client/libtalker_helper.a: client/CMakeFiles/talker_helper.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/stdmatrix/Desktop/chatex/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libtalker_helper.a"
	cd /mnt/c/Users/stdmatrix/Desktop/chatex/cmake-build-debug/client && $(CMAKE_COMMAND) -P CMakeFiles/talker_helper.dir/cmake_clean_target.cmake
	cd /mnt/c/Users/stdmatrix/Desktop/chatex/cmake-build-debug/client && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/talker_helper.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
client/CMakeFiles/talker_helper.dir/build: client/libtalker_helper.a
.PHONY : client/CMakeFiles/talker_helper.dir/build

client/CMakeFiles/talker_helper.dir/clean:
	cd /mnt/c/Users/stdmatrix/Desktop/chatex/cmake-build-debug/client && $(CMAKE_COMMAND) -P CMakeFiles/talker_helper.dir/cmake_clean.cmake
.PHONY : client/CMakeFiles/talker_helper.dir/clean

client/CMakeFiles/talker_helper.dir/depend:
	cd /mnt/c/Users/stdmatrix/Desktop/chatex/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/stdmatrix/Desktop/chatex /mnt/c/Users/stdmatrix/Desktop/chatex/client /mnt/c/Users/stdmatrix/Desktop/chatex/cmake-build-debug /mnt/c/Users/stdmatrix/Desktop/chatex/cmake-build-debug/client /mnt/c/Users/stdmatrix/Desktop/chatex/cmake-build-debug/client/CMakeFiles/talker_helper.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : client/CMakeFiles/talker_helper.dir/depend
