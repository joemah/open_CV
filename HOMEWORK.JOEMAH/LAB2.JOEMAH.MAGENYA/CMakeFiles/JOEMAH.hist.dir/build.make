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
CMAKE_SOURCE_DIR = /home/joe-mah/Desktop/openCV/HOMEWORK.JOEMAH/LAB2.JOEMAH.MAGENYA

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joe-mah/Desktop/openCV/HOMEWORK.JOEMAH/LAB2.JOEMAH.MAGENYA

# Include any dependencies generated for this target.
include CMakeFiles/JOEMAH.hist.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/JOEMAH.hist.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/JOEMAH.hist.dir/flags.make

CMakeFiles/JOEMAH.hist.dir/JOEMAH.hist.cpp.o: CMakeFiles/JOEMAH.hist.dir/flags.make
CMakeFiles/JOEMAH.hist.dir/JOEMAH.hist.cpp.o: JOEMAH.hist.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joe-mah/Desktop/openCV/HOMEWORK.JOEMAH/LAB2.JOEMAH.MAGENYA/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/JOEMAH.hist.dir/JOEMAH.hist.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/JOEMAH.hist.dir/JOEMAH.hist.cpp.o -c /home/joe-mah/Desktop/openCV/HOMEWORK.JOEMAH/LAB2.JOEMAH.MAGENYA/JOEMAH.hist.cpp

CMakeFiles/JOEMAH.hist.dir/JOEMAH.hist.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/JOEMAH.hist.dir/JOEMAH.hist.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joe-mah/Desktop/openCV/HOMEWORK.JOEMAH/LAB2.JOEMAH.MAGENYA/JOEMAH.hist.cpp > CMakeFiles/JOEMAH.hist.dir/JOEMAH.hist.cpp.i

CMakeFiles/JOEMAH.hist.dir/JOEMAH.hist.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/JOEMAH.hist.dir/JOEMAH.hist.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joe-mah/Desktop/openCV/HOMEWORK.JOEMAH/LAB2.JOEMAH.MAGENYA/JOEMAH.hist.cpp -o CMakeFiles/JOEMAH.hist.dir/JOEMAH.hist.cpp.s

# Object files for target JOEMAH.hist
JOEMAH_hist_OBJECTS = \
"CMakeFiles/JOEMAH.hist.dir/JOEMAH.hist.cpp.o"

# External object files for target JOEMAH.hist
JOEMAH_hist_EXTERNAL_OBJECTS =

JOEMAH.hist: CMakeFiles/JOEMAH.hist.dir/JOEMAH.hist.cpp.o
JOEMAH.hist: CMakeFiles/JOEMAH.hist.dir/build.make
JOEMAH.hist: /usr/local/lib/libopencv_dnn.so.4.3.0
JOEMAH.hist: /usr/local/lib/libopencv_gapi.so.4.3.0
JOEMAH.hist: /usr/local/lib/libopencv_highgui.so.4.3.0
JOEMAH.hist: /usr/local/lib/libopencv_ml.so.4.3.0
JOEMAH.hist: /usr/local/lib/libopencv_objdetect.so.4.3.0
JOEMAH.hist: /usr/local/lib/libopencv_photo.so.4.3.0
JOEMAH.hist: /usr/local/lib/libopencv_stitching.so.4.3.0
JOEMAH.hist: /usr/local/lib/libopencv_video.so.4.3.0
JOEMAH.hist: /usr/local/lib/libopencv_videoio.so.4.3.0
JOEMAH.hist: /usr/local/lib/libopencv_imgcodecs.so.4.3.0
JOEMAH.hist: /usr/local/lib/libopencv_calib3d.so.4.3.0
JOEMAH.hist: /usr/local/lib/libopencv_features2d.so.4.3.0
JOEMAH.hist: /usr/local/lib/libopencv_flann.so.4.3.0
JOEMAH.hist: /usr/local/lib/libopencv_imgproc.so.4.3.0
JOEMAH.hist: /usr/local/lib/libopencv_core.so.4.3.0
JOEMAH.hist: CMakeFiles/JOEMAH.hist.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/joe-mah/Desktop/openCV/HOMEWORK.JOEMAH/LAB2.JOEMAH.MAGENYA/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable JOEMAH.hist"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/JOEMAH.hist.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/JOEMAH.hist.dir/build: JOEMAH.hist

.PHONY : CMakeFiles/JOEMAH.hist.dir/build

CMakeFiles/JOEMAH.hist.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/JOEMAH.hist.dir/cmake_clean.cmake
.PHONY : CMakeFiles/JOEMAH.hist.dir/clean

CMakeFiles/JOEMAH.hist.dir/depend:
	cd /home/joe-mah/Desktop/openCV/HOMEWORK.JOEMAH/LAB2.JOEMAH.MAGENYA && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joe-mah/Desktop/openCV/HOMEWORK.JOEMAH/LAB2.JOEMAH.MAGENYA /home/joe-mah/Desktop/openCV/HOMEWORK.JOEMAH/LAB2.JOEMAH.MAGENYA /home/joe-mah/Desktop/openCV/HOMEWORK.JOEMAH/LAB2.JOEMAH.MAGENYA /home/joe-mah/Desktop/openCV/HOMEWORK.JOEMAH/LAB2.JOEMAH.MAGENYA /home/joe-mah/Desktop/openCV/HOMEWORK.JOEMAH/LAB2.JOEMAH.MAGENYA/CMakeFiles/JOEMAH.hist.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/JOEMAH.hist.dir/depend

