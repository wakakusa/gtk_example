# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hiro/Projects/library/test/02.cmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hiro/Projects/library/test/02.cmake

# Include any dependencies generated for this target.
include lib/CMakeFiles/library.dir/depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/library.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/library.dir/flags.make

lib/CMakeFiles/library.dir/library.c.o: lib/CMakeFiles/library.dir/flags.make
lib/CMakeFiles/library.dir/library.c.o: lib/library.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/hiro/Projects/library/test/02.cmake/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object lib/CMakeFiles/library.dir/library.c.o"
	cd /home/hiro/Projects/library/test/02.cmake/lib && gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/library.dir/library.c.o   -c /home/hiro/Projects/library/test/02.cmake/lib/library.c

lib/CMakeFiles/library.dir/library.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/library.dir/library.c.i"
	cd /home/hiro/Projects/library/test/02.cmake/lib && gcc  $(C_DEFINES) $(C_FLAGS) -E /home/hiro/Projects/library/test/02.cmake/lib/library.c > CMakeFiles/library.dir/library.c.i

lib/CMakeFiles/library.dir/library.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/library.dir/library.c.s"
	cd /home/hiro/Projects/library/test/02.cmake/lib && gcc  $(C_DEFINES) $(C_FLAGS) -S /home/hiro/Projects/library/test/02.cmake/lib/library.c -o CMakeFiles/library.dir/library.c.s

lib/CMakeFiles/library.dir/library.c.o.requires:
.PHONY : lib/CMakeFiles/library.dir/library.c.o.requires

lib/CMakeFiles/library.dir/library.c.o.provides: lib/CMakeFiles/library.dir/library.c.o.requires
	$(MAKE) -f lib/CMakeFiles/library.dir/build.make lib/CMakeFiles/library.dir/library.c.o.provides.build
.PHONY : lib/CMakeFiles/library.dir/library.c.o.provides

lib/CMakeFiles/library.dir/library.c.o.provides.build: lib/CMakeFiles/library.dir/library.c.o

# Object files for target library
library_OBJECTS = \
"CMakeFiles/library.dir/library.c.o"

# External object files for target library
library_EXTERNAL_OBJECTS =

lib/liblibrary.so: lib/CMakeFiles/library.dir/library.c.o
lib/liblibrary.so: lib/CMakeFiles/library.dir/build.make
lib/liblibrary.so: lib/CMakeFiles/library.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library liblibrary.so"
	cd /home/hiro/Projects/library/test/02.cmake/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/library.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/library.dir/build: lib/liblibrary.so
.PHONY : lib/CMakeFiles/library.dir/build

lib/CMakeFiles/library.dir/requires: lib/CMakeFiles/library.dir/library.c.o.requires
.PHONY : lib/CMakeFiles/library.dir/requires

lib/CMakeFiles/library.dir/clean:
	cd /home/hiro/Projects/library/test/02.cmake/lib && $(CMAKE_COMMAND) -P CMakeFiles/library.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/library.dir/clean

lib/CMakeFiles/library.dir/depend:
	cd /home/hiro/Projects/library/test/02.cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hiro/Projects/library/test/02.cmake /home/hiro/Projects/library/test/02.cmake/lib /home/hiro/Projects/library/test/02.cmake /home/hiro/Projects/library/test/02.cmake/lib /home/hiro/Projects/library/test/02.cmake/lib/CMakeFiles/library.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/library.dir/depend

