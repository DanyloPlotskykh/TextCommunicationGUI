# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = /snap/cmake/1384/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1384/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/user/p/TextCommunicationGUI

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/p/TextCommunicationGUI/build

# Utility rule file for test_project_autogen.

# Include any custom commands dependencies for this target.
include _client/CMakeFiles/test_project_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include _client/CMakeFiles/test_project_autogen.dir/progress.make

_client/CMakeFiles/test_project_autogen: _client/test_project_autogen/timestamp

_client/test_project_autogen/timestamp: /usr/lib/qt5/bin/moc
_client/test_project_autogen/timestamp: _client/CMakeFiles/test_project_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/user/p/TextCommunicationGUI/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target test_project"
	cd /home/user/p/TextCommunicationGUI/build/_client && /snap/cmake/1384/bin/cmake -E cmake_autogen /home/user/p/TextCommunicationGUI/build/_client/CMakeFiles/test_project_autogen.dir/AutogenInfo.json ""
	cd /home/user/p/TextCommunicationGUI/build/_client && /snap/cmake/1384/bin/cmake -E touch /home/user/p/TextCommunicationGUI/build/_client/test_project_autogen/timestamp

test_project_autogen: _client/CMakeFiles/test_project_autogen
test_project_autogen: _client/test_project_autogen/timestamp
test_project_autogen: _client/CMakeFiles/test_project_autogen.dir/build.make
.PHONY : test_project_autogen

# Rule to build all files generated by this target.
_client/CMakeFiles/test_project_autogen.dir/build: test_project_autogen
.PHONY : _client/CMakeFiles/test_project_autogen.dir/build

_client/CMakeFiles/test_project_autogen.dir/clean:
	cd /home/user/p/TextCommunicationGUI/build/_client && $(CMAKE_COMMAND) -P CMakeFiles/test_project_autogen.dir/cmake_clean.cmake
.PHONY : _client/CMakeFiles/test_project_autogen.dir/clean

_client/CMakeFiles/test_project_autogen.dir/depend:
	cd /home/user/p/TextCommunicationGUI/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/p/TextCommunicationGUI /home/user/p/TextCommunicationGUI/_client /home/user/p/TextCommunicationGUI/build /home/user/p/TextCommunicationGUI/build/_client /home/user/p/TextCommunicationGUI/build/_client/CMakeFiles/test_project_autogen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : _client/CMakeFiles/test_project_autogen.dir/depend

