# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.3.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.3.2\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Gamedev\glpl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Gamedev\glpl\cmake-build-debug

# Utility rule file for copy-runtime-files.

# Include the progress variables for this target.
include CMakeFiles\copy-runtime-files.dir\progress.make

CMakeFiles\copy-runtime-files:
	echo >nul && "C:\Program Files\JetBrains\CLion 2019.3.2\bin\cmake\win\bin\cmake.exe" -E copy_directory D:/Gamedev/glpl/assets D:/Gamedev/glpl/cmake-build-debug/assets

copy-runtime-files: CMakeFiles\copy-runtime-files
copy-runtime-files: CMakeFiles\copy-runtime-files.dir\build.make

.PHONY : copy-runtime-files

# Rule to build all files generated by this target.
CMakeFiles\copy-runtime-files.dir\build: copy-runtime-files

.PHONY : CMakeFiles\copy-runtime-files.dir\build

CMakeFiles\copy-runtime-files.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\copy-runtime-files.dir\cmake_clean.cmake
.PHONY : CMakeFiles\copy-runtime-files.dir\clean

CMakeFiles\copy-runtime-files.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" D:\Gamedev\glpl D:\Gamedev\glpl D:\Gamedev\glpl\cmake-build-debug D:\Gamedev\glpl\cmake-build-debug D:\Gamedev\glpl\cmake-build-debug\CMakeFiles\copy-runtime-files.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\copy-runtime-files.dir\depend
