# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/joe-mah/Desktop/openCV

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joe-mah/Desktop/openCV

# Include any dependencies generated for this target.
include CMakeFiles/open.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/open.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/open.dir/flags.make

CMakeFiles/open.dir/open.cpp.o: CMakeFiles/open.dir/flags.make
CMakeFiles/open.dir/open.cpp.o: open.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joe-mah/Desktop/openCV/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/open.dir/open.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/open.dir/open.cpp.o -c /home/joe-mah/Desktop/openCV/open.cpp

CMakeFiles/open.dir/open.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/open.dir/open.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joe-mah/Desktop/openCV/open.cpp > CMakeFiles/open.dir/open.cpp.i

CMakeFiles/open.dir/open.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/open.dir/open.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joe-mah/Desktop/openCV/open.cpp -o CMakeFiles/open.dir/open.cpp.s

# Object files for target open
open_OBJECTS = \
"CMakeFiles/open.dir/open.cpp.o"

# External object files for target open
open_EXTERNAL_OBJECTS =

open: CMakeFiles/open.dir/open.cpp.o
open: CMakeFiles/open.dir/build.make
open: /usr/local/lib/libopencv_dnn.so.4.3.0
open: /usr/local/lib/libopencv_gapi.so.4.3.0
open: /usr/local/lib/libopencv_highgui.so.4.3.0
open: /usr/local/lib/libopencv_ml.so.4.3.0
open: /usr/local/lib/libopencv_objdetect.so.4.3.0
open: /usr/local/lib/libopencv_photo.so.4.3.0
open: /usr/local/lib/libopencv_stitching.so.4.3.0
open: /usr/local/lib/libopencv_video.so.4.3.0
open: /usr/local/lib/libopencv_videoio.so.4.3.0
open: /usr/local/lib/libopencv_imgcodecs.so.4.3.0
open: /usr/local/lib/libopencv_calib3d.so.4.3.0
open: /usr/local/lib/libopencv_features2d.so.4.3.0
open: /usr/local/lib/libopencv_flann.so.4.3.0
open: /usr/local/lib/libopencv_imgproc.so.4.3.0
open: /usr/local/lib/libopencv_core.so.4.3.0
open: CMakeFiles/open.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/joe-mah/Desktop/openCV/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable open"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/open.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/open.dir/build: open

.PHONY : CMakeFiles/open.dir/build

CMakeFiles/open.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/open.dir/cmake_clean.cmake
.PHONY : CMakeFiles/open.dir/clean

CMakeFiles/open.dir/depend:
	cd /home/joe-mah/Desktop/openCV && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joe-mah/Desktop/openCV /home/joe-mah/Desktop/openCV /home/joe-mah/Desktop/openCV /home/joe-mah/Desktop/openCV /home/joe-mah/Desktop/openCV/CMakeFiles/open.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/open.dir/depend
