# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.26

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2023.2.2\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2023.2.2\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\ECOLE\Informatique\TP sem 3\TP3\TP2_Labyrinthe"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\ECOLE\Informatique\TP sem 3\TP3\TP2_Labyrinthe\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/TP2_Labyrinthe.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/TP2_Labyrinthe.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TP2_Labyrinthe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TP2_Labyrinthe.dir/flags.make

CMakeFiles/TP2_Labyrinthe.dir/main.c.obj: CMakeFiles/TP2_Labyrinthe.dir/flags.make
CMakeFiles/TP2_Labyrinthe.dir/main.c.obj: C:/ECOLE/Informatique/TP\ sem\ 3/TP3/TP2_Labyrinthe/main.c
CMakeFiles/TP2_Labyrinthe.dir/main.c.obj: CMakeFiles/TP2_Labyrinthe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\ECOLE\Informatique\TP sem 3\TP3\TP2_Labyrinthe\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/TP2_Labyrinthe.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TP2_Labyrinthe.dir/main.c.obj -MF CMakeFiles\TP2_Labyrinthe.dir\main.c.obj.d -o CMakeFiles\TP2_Labyrinthe.dir\main.c.obj -c "C:\ECOLE\Informatique\TP sem 3\TP3\TP2_Labyrinthe\main.c"

CMakeFiles/TP2_Labyrinthe.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TP2_Labyrinthe.dir/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\ECOLE\Informatique\TP sem 3\TP3\TP2_Labyrinthe\main.c" > CMakeFiles\TP2_Labyrinthe.dir\main.c.i

CMakeFiles/TP2_Labyrinthe.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TP2_Labyrinthe.dir/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\ECOLE\Informatique\TP sem 3\TP3\TP2_Labyrinthe\main.c" -o CMakeFiles\TP2_Labyrinthe.dir\main.c.s

CMakeFiles/TP2_Labyrinthe.dir/fifo.c.obj: CMakeFiles/TP2_Labyrinthe.dir/flags.make
CMakeFiles/TP2_Labyrinthe.dir/fifo.c.obj: C:/ECOLE/Informatique/TP\ sem\ 3/TP3/TP2_Labyrinthe/fifo.c
CMakeFiles/TP2_Labyrinthe.dir/fifo.c.obj: CMakeFiles/TP2_Labyrinthe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\ECOLE\Informatique\TP sem 3\TP3\TP2_Labyrinthe\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/TP2_Labyrinthe.dir/fifo.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TP2_Labyrinthe.dir/fifo.c.obj -MF CMakeFiles\TP2_Labyrinthe.dir\fifo.c.obj.d -o CMakeFiles\TP2_Labyrinthe.dir\fifo.c.obj -c "C:\ECOLE\Informatique\TP sem 3\TP3\TP2_Labyrinthe\fifo.c"

CMakeFiles/TP2_Labyrinthe.dir/fifo.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TP2_Labyrinthe.dir/fifo.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\ECOLE\Informatique\TP sem 3\TP3\TP2_Labyrinthe\fifo.c" > CMakeFiles\TP2_Labyrinthe.dir\fifo.c.i

CMakeFiles/TP2_Labyrinthe.dir/fifo.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TP2_Labyrinthe.dir/fifo.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\ECOLE\Informatique\TP sem 3\TP3\TP2_Labyrinthe\fifo.c" -o CMakeFiles\TP2_Labyrinthe.dir\fifo.c.s

# Object files for target TP2_Labyrinthe
TP2_Labyrinthe_OBJECTS = \
"CMakeFiles/TP2_Labyrinthe.dir/main.c.obj" \
"CMakeFiles/TP2_Labyrinthe.dir/fifo.c.obj"

# External object files for target TP2_Labyrinthe
TP2_Labyrinthe_EXTERNAL_OBJECTS =

TP2_Labyrinthe.exe: CMakeFiles/TP2_Labyrinthe.dir/main.c.obj
TP2_Labyrinthe.exe: CMakeFiles/TP2_Labyrinthe.dir/fifo.c.obj
TP2_Labyrinthe.exe: CMakeFiles/TP2_Labyrinthe.dir/build.make
TP2_Labyrinthe.exe: CMakeFiles/TP2_Labyrinthe.dir/linkLibs.rsp
TP2_Labyrinthe.exe: CMakeFiles/TP2_Labyrinthe.dir/objects1.rsp
TP2_Labyrinthe.exe: CMakeFiles/TP2_Labyrinthe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\ECOLE\Informatique\TP sem 3\TP3\TP2_Labyrinthe\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable TP2_Labyrinthe.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\TP2_Labyrinthe.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TP2_Labyrinthe.dir/build: TP2_Labyrinthe.exe
.PHONY : CMakeFiles/TP2_Labyrinthe.dir/build

CMakeFiles/TP2_Labyrinthe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\TP2_Labyrinthe.dir\cmake_clean.cmake
.PHONY : CMakeFiles/TP2_Labyrinthe.dir/clean

CMakeFiles/TP2_Labyrinthe.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\ECOLE\Informatique\TP sem 3\TP3\TP2_Labyrinthe" "C:\ECOLE\Informatique\TP sem 3\TP3\TP2_Labyrinthe" "C:\ECOLE\Informatique\TP sem 3\TP3\TP2_Labyrinthe\cmake-build-debug" "C:\ECOLE\Informatique\TP sem 3\TP3\TP2_Labyrinthe\cmake-build-debug" "C:\ECOLE\Informatique\TP sem 3\TP3\TP2_Labyrinthe\cmake-build-debug\CMakeFiles\TP2_Labyrinthe.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/TP2_Labyrinthe.dir/depend

