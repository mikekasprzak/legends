# CMAKE generated file: DO NOT EDIT!
# Generated by "MSYS Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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
CMAKE_COMMAND = "/c/Program Files (x86)/CMake 2.8/bin/cmake.exe"

# The command to remove a file.
RM = "/c/Program Files (x86)/CMake 2.8/bin/cmake.exe" -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = "/c/Program Files (x86)/CMake 2.8/bin/cmake-gui.exe"

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /D/Build/bullet-2.78

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /D/Build/bullet-2.78

# Include any dependencies generated for this target.
include src/LinearMath/CMakeFiles/LinearMath.dir/depend.make

# Include the progress variables for this target.
include src/LinearMath/CMakeFiles/LinearMath.dir/progress.make

# Include the compile flags for this target's objects.
include src/LinearMath/CMakeFiles/LinearMath.dir/flags.make

src/LinearMath/CMakeFiles/LinearMath.dir/btAlignedAllocator.obj: src/LinearMath/CMakeFiles/LinearMath.dir/flags.make
src/LinearMath/CMakeFiles/LinearMath.dir/btAlignedAllocator.obj: src/LinearMath/btAlignedAllocator.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /D/Build/bullet-2.78/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/LinearMath/CMakeFiles/LinearMath.dir/btAlignedAllocator.obj"
	cd /D/Build/bullet-2.78/src/LinearMath && /C/MinGW/bin/g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/LinearMath.dir/btAlignedAllocator.obj -c /D/Build/bullet-2.78/src/LinearMath/btAlignedAllocator.cpp

src/LinearMath/CMakeFiles/LinearMath.dir/btAlignedAllocator.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LinearMath.dir/btAlignedAllocator.i"
	cd /D/Build/bullet-2.78/src/LinearMath && /C/MinGW/bin/g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E /D/Build/bullet-2.78/src/LinearMath/btAlignedAllocator.cpp > CMakeFiles/LinearMath.dir/btAlignedAllocator.i

src/LinearMath/CMakeFiles/LinearMath.dir/btAlignedAllocator.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LinearMath.dir/btAlignedAllocator.s"
	cd /D/Build/bullet-2.78/src/LinearMath && /C/MinGW/bin/g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S /D/Build/bullet-2.78/src/LinearMath/btAlignedAllocator.cpp -o CMakeFiles/LinearMath.dir/btAlignedAllocator.s

src/LinearMath/CMakeFiles/LinearMath.dir/btAlignedAllocator.obj.requires:
.PHONY : src/LinearMath/CMakeFiles/LinearMath.dir/btAlignedAllocator.obj.requires

src/LinearMath/CMakeFiles/LinearMath.dir/btAlignedAllocator.obj.provides: src/LinearMath/CMakeFiles/LinearMath.dir/btAlignedAllocator.obj.requires
	$(MAKE) -f src/LinearMath/CMakeFiles/LinearMath.dir/build.make src/LinearMath/CMakeFiles/LinearMath.dir/btAlignedAllocator.obj.provides.build
.PHONY : src/LinearMath/CMakeFiles/LinearMath.dir/btAlignedAllocator.obj.provides

src/LinearMath/CMakeFiles/LinearMath.dir/btAlignedAllocator.obj.provides.build: src/LinearMath/CMakeFiles/LinearMath.dir/btAlignedAllocator.obj

src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHull.obj: src/LinearMath/CMakeFiles/LinearMath.dir/flags.make
src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHull.obj: src/LinearMath/btConvexHull.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /D/Build/bullet-2.78/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHull.obj"
	cd /D/Build/bullet-2.78/src/LinearMath && /C/MinGW/bin/g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/LinearMath.dir/btConvexHull.obj -c /D/Build/bullet-2.78/src/LinearMath/btConvexHull.cpp

src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHull.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LinearMath.dir/btConvexHull.i"
	cd /D/Build/bullet-2.78/src/LinearMath && /C/MinGW/bin/g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E /D/Build/bullet-2.78/src/LinearMath/btConvexHull.cpp > CMakeFiles/LinearMath.dir/btConvexHull.i

src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHull.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LinearMath.dir/btConvexHull.s"
	cd /D/Build/bullet-2.78/src/LinearMath && /C/MinGW/bin/g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S /D/Build/bullet-2.78/src/LinearMath/btConvexHull.cpp -o CMakeFiles/LinearMath.dir/btConvexHull.s

src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHull.obj.requires:
.PHONY : src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHull.obj.requires

src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHull.obj.provides: src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHull.obj.requires
	$(MAKE) -f src/LinearMath/CMakeFiles/LinearMath.dir/build.make src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHull.obj.provides.build
.PHONY : src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHull.obj.provides

src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHull.obj.provides.build: src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHull.obj

src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHullComputer.obj: src/LinearMath/CMakeFiles/LinearMath.dir/flags.make
src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHullComputer.obj: src/LinearMath/btConvexHullComputer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /D/Build/bullet-2.78/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHullComputer.obj"
	cd /D/Build/bullet-2.78/src/LinearMath && /C/MinGW/bin/g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/LinearMath.dir/btConvexHullComputer.obj -c /D/Build/bullet-2.78/src/LinearMath/btConvexHullComputer.cpp

src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHullComputer.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LinearMath.dir/btConvexHullComputer.i"
	cd /D/Build/bullet-2.78/src/LinearMath && /C/MinGW/bin/g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E /D/Build/bullet-2.78/src/LinearMath/btConvexHullComputer.cpp > CMakeFiles/LinearMath.dir/btConvexHullComputer.i

src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHullComputer.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LinearMath.dir/btConvexHullComputer.s"
	cd /D/Build/bullet-2.78/src/LinearMath && /C/MinGW/bin/g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S /D/Build/bullet-2.78/src/LinearMath/btConvexHullComputer.cpp -o CMakeFiles/LinearMath.dir/btConvexHullComputer.s

src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHullComputer.obj.requires:
.PHONY : src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHullComputer.obj.requires

src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHullComputer.obj.provides: src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHullComputer.obj.requires
	$(MAKE) -f src/LinearMath/CMakeFiles/LinearMath.dir/build.make src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHullComputer.obj.provides.build
.PHONY : src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHullComputer.obj.provides

src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHullComputer.obj.provides.build: src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHullComputer.obj

src/LinearMath/CMakeFiles/LinearMath.dir/btGeometryUtil.obj: src/LinearMath/CMakeFiles/LinearMath.dir/flags.make
src/LinearMath/CMakeFiles/LinearMath.dir/btGeometryUtil.obj: src/LinearMath/btGeometryUtil.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /D/Build/bullet-2.78/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/LinearMath/CMakeFiles/LinearMath.dir/btGeometryUtil.obj"
	cd /D/Build/bullet-2.78/src/LinearMath && /C/MinGW/bin/g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/LinearMath.dir/btGeometryUtil.obj -c /D/Build/bullet-2.78/src/LinearMath/btGeometryUtil.cpp

src/LinearMath/CMakeFiles/LinearMath.dir/btGeometryUtil.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LinearMath.dir/btGeometryUtil.i"
	cd /D/Build/bullet-2.78/src/LinearMath && /C/MinGW/bin/g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E /D/Build/bullet-2.78/src/LinearMath/btGeometryUtil.cpp > CMakeFiles/LinearMath.dir/btGeometryUtil.i

src/LinearMath/CMakeFiles/LinearMath.dir/btGeometryUtil.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LinearMath.dir/btGeometryUtil.s"
	cd /D/Build/bullet-2.78/src/LinearMath && /C/MinGW/bin/g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S /D/Build/bullet-2.78/src/LinearMath/btGeometryUtil.cpp -o CMakeFiles/LinearMath.dir/btGeometryUtil.s

src/LinearMath/CMakeFiles/LinearMath.dir/btGeometryUtil.obj.requires:
.PHONY : src/LinearMath/CMakeFiles/LinearMath.dir/btGeometryUtil.obj.requires

src/LinearMath/CMakeFiles/LinearMath.dir/btGeometryUtil.obj.provides: src/LinearMath/CMakeFiles/LinearMath.dir/btGeometryUtil.obj.requires
	$(MAKE) -f src/LinearMath/CMakeFiles/LinearMath.dir/build.make src/LinearMath/CMakeFiles/LinearMath.dir/btGeometryUtil.obj.provides.build
.PHONY : src/LinearMath/CMakeFiles/LinearMath.dir/btGeometryUtil.obj.provides

src/LinearMath/CMakeFiles/LinearMath.dir/btGeometryUtil.obj.provides.build: src/LinearMath/CMakeFiles/LinearMath.dir/btGeometryUtil.obj

src/LinearMath/CMakeFiles/LinearMath.dir/btQuickprof.obj: src/LinearMath/CMakeFiles/LinearMath.dir/flags.make
src/LinearMath/CMakeFiles/LinearMath.dir/btQuickprof.obj: src/LinearMath/btQuickprof.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /D/Build/bullet-2.78/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/LinearMath/CMakeFiles/LinearMath.dir/btQuickprof.obj"
	cd /D/Build/bullet-2.78/src/LinearMath && /C/MinGW/bin/g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/LinearMath.dir/btQuickprof.obj -c /D/Build/bullet-2.78/src/LinearMath/btQuickprof.cpp

src/LinearMath/CMakeFiles/LinearMath.dir/btQuickprof.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LinearMath.dir/btQuickprof.i"
	cd /D/Build/bullet-2.78/src/LinearMath && /C/MinGW/bin/g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E /D/Build/bullet-2.78/src/LinearMath/btQuickprof.cpp > CMakeFiles/LinearMath.dir/btQuickprof.i

src/LinearMath/CMakeFiles/LinearMath.dir/btQuickprof.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LinearMath.dir/btQuickprof.s"
	cd /D/Build/bullet-2.78/src/LinearMath && /C/MinGW/bin/g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S /D/Build/bullet-2.78/src/LinearMath/btQuickprof.cpp -o CMakeFiles/LinearMath.dir/btQuickprof.s

src/LinearMath/CMakeFiles/LinearMath.dir/btQuickprof.obj.requires:
.PHONY : src/LinearMath/CMakeFiles/LinearMath.dir/btQuickprof.obj.requires

src/LinearMath/CMakeFiles/LinearMath.dir/btQuickprof.obj.provides: src/LinearMath/CMakeFiles/LinearMath.dir/btQuickprof.obj.requires
	$(MAKE) -f src/LinearMath/CMakeFiles/LinearMath.dir/build.make src/LinearMath/CMakeFiles/LinearMath.dir/btQuickprof.obj.provides.build
.PHONY : src/LinearMath/CMakeFiles/LinearMath.dir/btQuickprof.obj.provides

src/LinearMath/CMakeFiles/LinearMath.dir/btQuickprof.obj.provides.build: src/LinearMath/CMakeFiles/LinearMath.dir/btQuickprof.obj

src/LinearMath/CMakeFiles/LinearMath.dir/btSerializer.obj: src/LinearMath/CMakeFiles/LinearMath.dir/flags.make
src/LinearMath/CMakeFiles/LinearMath.dir/btSerializer.obj: src/LinearMath/btSerializer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /D/Build/bullet-2.78/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/LinearMath/CMakeFiles/LinearMath.dir/btSerializer.obj"
	cd /D/Build/bullet-2.78/src/LinearMath && /C/MinGW/bin/g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/LinearMath.dir/btSerializer.obj -c /D/Build/bullet-2.78/src/LinearMath/btSerializer.cpp

src/LinearMath/CMakeFiles/LinearMath.dir/btSerializer.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LinearMath.dir/btSerializer.i"
	cd /D/Build/bullet-2.78/src/LinearMath && /C/MinGW/bin/g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E /D/Build/bullet-2.78/src/LinearMath/btSerializer.cpp > CMakeFiles/LinearMath.dir/btSerializer.i

src/LinearMath/CMakeFiles/LinearMath.dir/btSerializer.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LinearMath.dir/btSerializer.s"
	cd /D/Build/bullet-2.78/src/LinearMath && /C/MinGW/bin/g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S /D/Build/bullet-2.78/src/LinearMath/btSerializer.cpp -o CMakeFiles/LinearMath.dir/btSerializer.s

src/LinearMath/CMakeFiles/LinearMath.dir/btSerializer.obj.requires:
.PHONY : src/LinearMath/CMakeFiles/LinearMath.dir/btSerializer.obj.requires

src/LinearMath/CMakeFiles/LinearMath.dir/btSerializer.obj.provides: src/LinearMath/CMakeFiles/LinearMath.dir/btSerializer.obj.requires
	$(MAKE) -f src/LinearMath/CMakeFiles/LinearMath.dir/build.make src/LinearMath/CMakeFiles/LinearMath.dir/btSerializer.obj.provides.build
.PHONY : src/LinearMath/CMakeFiles/LinearMath.dir/btSerializer.obj.provides

src/LinearMath/CMakeFiles/LinearMath.dir/btSerializer.obj.provides.build: src/LinearMath/CMakeFiles/LinearMath.dir/btSerializer.obj

# Object files for target LinearMath
LinearMath_OBJECTS = \
"CMakeFiles/LinearMath.dir/btAlignedAllocator.obj" \
"CMakeFiles/LinearMath.dir/btConvexHull.obj" \
"CMakeFiles/LinearMath.dir/btConvexHullComputer.obj" \
"CMakeFiles/LinearMath.dir/btGeometryUtil.obj" \
"CMakeFiles/LinearMath.dir/btQuickprof.obj" \
"CMakeFiles/LinearMath.dir/btSerializer.obj"

# External object files for target LinearMath
LinearMath_EXTERNAL_OBJECTS =

lib/libLinearMath.a: src/LinearMath/CMakeFiles/LinearMath.dir/btAlignedAllocator.obj
lib/libLinearMath.a: src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHull.obj
lib/libLinearMath.a: src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHullComputer.obj
lib/libLinearMath.a: src/LinearMath/CMakeFiles/LinearMath.dir/btGeometryUtil.obj
lib/libLinearMath.a: src/LinearMath/CMakeFiles/LinearMath.dir/btQuickprof.obj
lib/libLinearMath.a: src/LinearMath/CMakeFiles/LinearMath.dir/btSerializer.obj
lib/libLinearMath.a: src/LinearMath/CMakeFiles/LinearMath.dir/build.make
lib/libLinearMath.a: src/LinearMath/CMakeFiles/LinearMath.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library ../../lib/libLinearMath.a"
	cd /D/Build/bullet-2.78/src/LinearMath && $(CMAKE_COMMAND) -P CMakeFiles/LinearMath.dir/cmake_clean_target.cmake
	cd /D/Build/bullet-2.78/src/LinearMath && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LinearMath.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/LinearMath/CMakeFiles/LinearMath.dir/build: lib/libLinearMath.a
.PHONY : src/LinearMath/CMakeFiles/LinearMath.dir/build

src/LinearMath/CMakeFiles/LinearMath.dir/requires: src/LinearMath/CMakeFiles/LinearMath.dir/btAlignedAllocator.obj.requires
src/LinearMath/CMakeFiles/LinearMath.dir/requires: src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHull.obj.requires
src/LinearMath/CMakeFiles/LinearMath.dir/requires: src/LinearMath/CMakeFiles/LinearMath.dir/btConvexHullComputer.obj.requires
src/LinearMath/CMakeFiles/LinearMath.dir/requires: src/LinearMath/CMakeFiles/LinearMath.dir/btGeometryUtil.obj.requires
src/LinearMath/CMakeFiles/LinearMath.dir/requires: src/LinearMath/CMakeFiles/LinearMath.dir/btQuickprof.obj.requires
src/LinearMath/CMakeFiles/LinearMath.dir/requires: src/LinearMath/CMakeFiles/LinearMath.dir/btSerializer.obj.requires
.PHONY : src/LinearMath/CMakeFiles/LinearMath.dir/requires

src/LinearMath/CMakeFiles/LinearMath.dir/clean:
	cd /D/Build/bullet-2.78/src/LinearMath && $(CMAKE_COMMAND) -P CMakeFiles/LinearMath.dir/cmake_clean.cmake
.PHONY : src/LinearMath/CMakeFiles/LinearMath.dir/clean

src/LinearMath/CMakeFiles/LinearMath.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MSYS Makefiles" /D/Build/bullet-2.78 /D/Build/bullet-2.78/src/LinearMath /D/Build/bullet-2.78 /D/Build/bullet-2.78/src/LinearMath /D/Build/bullet-2.78/src/LinearMath/CMakeFiles/LinearMath.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/LinearMath/CMakeFiles/LinearMath.dir/depend
