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
CMAKE_SOURCE_DIR = /home/joe-mah/Desktop/openCV/projects

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joe-mah/Desktop/openCV/projects

# Include any dependencies generated for this target.
include CMakeFiles/exam.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/exam.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/exam.dir/flags.make

CMakeFiles/exam.dir/exam.cpp.o: CMakeFiles/exam.dir/flags.make
CMakeFiles/exam.dir/exam.cpp.o: exam.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joe-mah/Desktop/openCV/projects/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/exam.dir/exam.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exam.dir/exam.cpp.o -c /home/joe-mah/Desktop/openCV/projects/exam.cpp

CMakeFiles/exam.dir/exam.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exam.dir/exam.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joe-mah/Desktop/openCV/projects/exam.cpp > CMakeFiles/exam.dir/exam.cpp.i

CMakeFiles/exam.dir/exam.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exam.dir/exam.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joe-mah/Desktop/openCV/projects/exam.cpp -o CMakeFiles/exam.dir/exam.cpp.s

# Object files for target exam
exam_OBJECTS = \
"CMakeFiles/exam.dir/exam.cpp.o"

# External object files for target exam
exam_EXTERNAL_OBJECTS =

exam: CMakeFiles/exam.dir/exam.cpp.o
exam: CMakeFiles/exam.dir/build.make
exam: /usr/local/lib/libopencv_dnn.so.4.3.0
exam: /usr/local/lib/libopencv_gapi.so.4.3.0
exam: /usr/local/lib/libopencv_highgui.so.4.3.0
exam: /usr/local/lib/libopencv_ml.so.4.3.0
exam: /usr/local/lib/libopencv_objdetect.so.4.3.0
exam: /usr/local/lib/libopencv_photo.so.4.3.0
exam: /usr/local/lib/libopencv_stitching.so.4.3.0
exam: /usr/local/lib/libopencv_video.so.4.3.0
exam: /usr/local/lib/libopencv_videoio.so.4.3.0
exam: /usr/local/lib/libopencv_imgcodecs.so.4.3.0
exam: /usr/local/lib/libopencv_calib3d.so.4.3.0
exam: /usr/local/lib/libopencv_features2d.so.4.3.0
exam: /usr/local/lib/libopencv_flann.so.4.3.0
exam: /usr/local/lib/libopencv_imgproc.so.4.3.0
exam: /usr/local/lib/libopencv_core.so.4.3.0
exam: CMakeFiles/exam.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/joe-mah/Desktop/openCV/projects/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable exam"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/exam.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/exam.dir/build: exam

.PHONY : CMakeFiles/exam.dir/build

CMakeFiles/exam.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/exam.dir/cmake_clean.cmake
.PHONY : CMakeFiles/exam.dir/clean

CMakeFiles/exam.dir/depend:
	cd /home/joe-mah/Desktop/openCV/projects && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joe-mah/Desktop/openCV/projects /home/joe-mah/Desktop/openCV/projects /home/joe-mah/Desktop/openCV/projects /home/joe-mah/Desktop/openCV/projects /home/joe-mah/Desktop/openCV/projects/CMakeFiles/exam.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/exam.dir/depend

