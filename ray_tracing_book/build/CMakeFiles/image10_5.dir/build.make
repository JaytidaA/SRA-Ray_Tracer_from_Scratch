# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/rakshitha/Desktop/ray_tracing_book

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rakshitha/Desktop/ray_tracing_book/build

# Include any dependencies generated for this target.
include CMakeFiles/image10_5.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/image10_5.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/image10_5.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/image10_5.dir/flags.make

CMakeFiles/image10_5.dir/10.5.cpp.o: CMakeFiles/image10_5.dir/flags.make
CMakeFiles/image10_5.dir/10.5.cpp.o: /home/rakshitha/Desktop/ray_tracing_book/10.5.cpp
CMakeFiles/image10_5.dir/10.5.cpp.o: CMakeFiles/image10_5.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/rakshitha/Desktop/ray_tracing_book/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/image10_5.dir/10.5.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/image10_5.dir/10.5.cpp.o -MF CMakeFiles/image10_5.dir/10.5.cpp.o.d -o CMakeFiles/image10_5.dir/10.5.cpp.o -c /home/rakshitha/Desktop/ray_tracing_book/10.5.cpp

CMakeFiles/image10_5.dir/10.5.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/image10_5.dir/10.5.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rakshitha/Desktop/ray_tracing_book/10.5.cpp > CMakeFiles/image10_5.dir/10.5.cpp.i

CMakeFiles/image10_5.dir/10.5.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/image10_5.dir/10.5.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rakshitha/Desktop/ray_tracing_book/10.5.cpp -o CMakeFiles/image10_5.dir/10.5.cpp.s

# Object files for target image10_5
image10_5_OBJECTS = \
"CMakeFiles/image10_5.dir/10.5.cpp.o"

# External object files for target image10_5
image10_5_EXTERNAL_OBJECTS =

image10_5: CMakeFiles/image10_5.dir/10.5.cpp.o
image10_5: CMakeFiles/image10_5.dir/build.make
image10_5: CMakeFiles/image10_5.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/rakshitha/Desktop/ray_tracing_book/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable image10_5"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/image10_5.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/image10_5.dir/build: image10_5
.PHONY : CMakeFiles/image10_5.dir/build

CMakeFiles/image10_5.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/image10_5.dir/cmake_clean.cmake
.PHONY : CMakeFiles/image10_5.dir/clean

CMakeFiles/image10_5.dir/depend:
	cd /home/rakshitha/Desktop/ray_tracing_book/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rakshitha/Desktop/ray_tracing_book /home/rakshitha/Desktop/ray_tracing_book /home/rakshitha/Desktop/ray_tracing_book/build /home/rakshitha/Desktop/ray_tracing_book/build /home/rakshitha/Desktop/ray_tracing_book/build/CMakeFiles/image10_5.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/image10_5.dir/depend

