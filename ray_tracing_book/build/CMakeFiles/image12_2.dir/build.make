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
include CMakeFiles/image12_2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/image12_2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/image12_2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/image12_2.dir/flags.make

CMakeFiles/image12_2.dir/12.2.cpp.o: CMakeFiles/image12_2.dir/flags.make
CMakeFiles/image12_2.dir/12.2.cpp.o: /home/rakshitha/Desktop/ray_tracing_book/12.2.cpp
CMakeFiles/image12_2.dir/12.2.cpp.o: CMakeFiles/image12_2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/rakshitha/Desktop/ray_tracing_book/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/image12_2.dir/12.2.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/image12_2.dir/12.2.cpp.o -MF CMakeFiles/image12_2.dir/12.2.cpp.o.d -o CMakeFiles/image12_2.dir/12.2.cpp.o -c /home/rakshitha/Desktop/ray_tracing_book/12.2.cpp

CMakeFiles/image12_2.dir/12.2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/image12_2.dir/12.2.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rakshitha/Desktop/ray_tracing_book/12.2.cpp > CMakeFiles/image12_2.dir/12.2.cpp.i

CMakeFiles/image12_2.dir/12.2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/image12_2.dir/12.2.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rakshitha/Desktop/ray_tracing_book/12.2.cpp -o CMakeFiles/image12_2.dir/12.2.cpp.s

# Object files for target image12_2
image12_2_OBJECTS = \
"CMakeFiles/image12_2.dir/12.2.cpp.o"

# External object files for target image12_2
image12_2_EXTERNAL_OBJECTS =

image12_2: CMakeFiles/image12_2.dir/12.2.cpp.o
image12_2: CMakeFiles/image12_2.dir/build.make
image12_2: CMakeFiles/image12_2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/rakshitha/Desktop/ray_tracing_book/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable image12_2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/image12_2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/image12_2.dir/build: image12_2
.PHONY : CMakeFiles/image12_2.dir/build

CMakeFiles/image12_2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/image12_2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/image12_2.dir/clean

CMakeFiles/image12_2.dir/depend:
	cd /home/rakshitha/Desktop/ray_tracing_book/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rakshitha/Desktop/ray_tracing_book /home/rakshitha/Desktop/ray_tracing_book /home/rakshitha/Desktop/ray_tracing_book/build /home/rakshitha/Desktop/ray_tracing_book/build /home/rakshitha/Desktop/ray_tracing_book/build/CMakeFiles/image12_2.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/image12_2.dir/depend

