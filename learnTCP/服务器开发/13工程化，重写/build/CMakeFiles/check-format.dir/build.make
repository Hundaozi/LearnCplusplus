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
CMAKE_SOURCE_DIR = /root/github/LearnCplusplus/learnTCP/服务器开发/13工程化，重写

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/github/LearnCplusplus/learnTCP/服务器开发/13工程化，重写/build

# Utility rule file for check-format.

# Include the progress variables for this target.
include CMakeFiles/check-format.dir/progress.make

CMakeFiles/check-format:
	../build_support/run_clang_format.py /usr/bin/clang-format /root/github/LearnCplusplus/learnTCP/服务器开发/13工程化，重写/build_support/clang_format_exclusions.txt --source_dirs /root/github/LearnCplusplus/learnTCP/服务器开发/13工程化，重写/src,/root/github/LearnCplusplus/learnTCP/服务器开发/13工程化，重写/test, --quiet

check-format: CMakeFiles/check-format
check-format: CMakeFiles/check-format.dir/build.make

.PHONY : check-format

# Rule to build all files generated by this target.
CMakeFiles/check-format.dir/build: check-format

.PHONY : CMakeFiles/check-format.dir/build

CMakeFiles/check-format.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/check-format.dir/cmake_clean.cmake
.PHONY : CMakeFiles/check-format.dir/clean

CMakeFiles/check-format.dir/depend:
	cd /root/github/LearnCplusplus/learnTCP/服务器开发/13工程化，重写/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/github/LearnCplusplus/learnTCP/服务器开发/13工程化，重写 /root/github/LearnCplusplus/learnTCP/服务器开发/13工程化，重写 /root/github/LearnCplusplus/learnTCP/服务器开发/13工程化，重写/build /root/github/LearnCplusplus/learnTCP/服务器开发/13工程化，重写/build /root/github/LearnCplusplus/learnTCP/服务器开发/13工程化，重写/build/CMakeFiles/check-format.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/check-format.dir/depend

