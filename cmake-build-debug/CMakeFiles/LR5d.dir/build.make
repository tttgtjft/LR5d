# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\ASUS TUF GAMING\CLionProjects\LR5d"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\ASUS TUF GAMING\CLionProjects\LR5d\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/LR5d.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/LR5d.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LR5d.dir/flags.make

CMakeFiles/LR5d.dir/main.c.obj: CMakeFiles/LR5d.dir/flags.make
CMakeFiles/LR5d.dir/main.c.obj: CMakeFiles/LR5d.dir/includes_C.rsp
CMakeFiles/LR5d.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\ASUS TUF GAMING\CLionProjects\LR5d\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/LR5d.dir/main.c.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\LR5d.dir\main.c.obj -c "C:\Users\ASUS TUF GAMING\CLionProjects\LR5d\main.c"

CMakeFiles/LR5d.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LR5d.dir/main.c.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\ASUS TUF GAMING\CLionProjects\LR5d\main.c" > CMakeFiles\LR5d.dir\main.c.i

CMakeFiles/LR5d.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LR5d.dir/main.c.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\ASUS TUF GAMING\CLionProjects\LR5d\main.c" -o CMakeFiles\LR5d.dir\main.c.s

# Object files for target LR5d
LR5d_OBJECTS = \
"CMakeFiles/LR5d.dir/main.c.obj"

# External object files for target LR5d
LR5d_EXTERNAL_OBJECTS =

LR5d.exe: CMakeFiles/LR5d.dir/main.c.obj
LR5d.exe: CMakeFiles/LR5d.dir/build.make
LR5d.exe: CMakeFiles/LR5d.dir/linklibs.rsp
LR5d.exe: CMakeFiles/LR5d.dir/objects1.rsp
LR5d.exe: CMakeFiles/LR5d.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\ASUS TUF GAMING\CLionProjects\LR5d\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable LR5d.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\LR5d.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LR5d.dir/build: LR5d.exe
.PHONY : CMakeFiles/LR5d.dir/build

CMakeFiles/LR5d.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\LR5d.dir\cmake_clean.cmake
.PHONY : CMakeFiles/LR5d.dir/clean

CMakeFiles/LR5d.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\ASUS TUF GAMING\CLionProjects\LR5d" "C:\Users\ASUS TUF GAMING\CLionProjects\LR5d" "C:\Users\ASUS TUF GAMING\CLionProjects\LR5d\cmake-build-debug" "C:\Users\ASUS TUF GAMING\CLionProjects\LR5d\cmake-build-debug" "C:\Users\ASUS TUF GAMING\CLionProjects\LR5d\cmake-build-debug\CMakeFiles\LR5d.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/LR5d.dir/depend

