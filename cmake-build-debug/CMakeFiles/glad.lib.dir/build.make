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

# Include any dependencies generated for this target.
include CMakeFiles\glad.lib.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\glad.lib.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\glad.lib.dir\flags.make

CMakeFiles\glad.lib.dir\src\glad\glad.c.obj: CMakeFiles\glad.lib.dir\flags.make
CMakeFiles\glad.lib.dir\src\glad\glad.c.obj: ..\src\glad\glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Gamedev\glpl\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/glad.lib.dir/src/glad/glad.c.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\glad.lib.dir\src\glad\glad.c.obj /FdCMakeFiles\glad.lib.dir\glad.lib.pdb /FS -c D:\Gamedev\glpl\src\glad\glad.c
<<

CMakeFiles\glad.lib.dir\src\glad\glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glad.lib.dir/src/glad/glad.c.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe > CMakeFiles\glad.lib.dir\src\glad\glad.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Gamedev\glpl\src\glad\glad.c
<<

CMakeFiles\glad.lib.dir\src\glad\glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glad.lib.dir/src/glad/glad.c.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\glad.lib.dir\src\glad\glad.c.s /c D:\Gamedev\glpl\src\glad\glad.c
<<

# Object files for target glad.lib
glad_lib_OBJECTS = \
"CMakeFiles\glad.lib.dir\src\glad\glad.c.obj"

# External object files for target glad.lib
glad_lib_EXTERNAL_OBJECTS =

glad.lib.lib: CMakeFiles\glad.lib.dir\src\glad\glad.c.obj
glad.lib.lib: CMakeFiles\glad.lib.dir\build.make
glad.lib.lib: CMakeFiles\glad.lib.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Gamedev\glpl\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library glad.lib.lib"
	$(CMAKE_COMMAND) -P CMakeFiles\glad.lib.dir\cmake_clean_target.cmake
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\link.exe /lib /nologo /machine:X86 /out:glad.lib.lib @CMakeFiles\glad.lib.dir\objects1.rsp 

# Rule to build all files generated by this target.
CMakeFiles\glad.lib.dir\build: glad.lib.lib

.PHONY : CMakeFiles\glad.lib.dir\build

CMakeFiles\glad.lib.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\glad.lib.dir\cmake_clean.cmake
.PHONY : CMakeFiles\glad.lib.dir\clean

CMakeFiles\glad.lib.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" D:\Gamedev\glpl D:\Gamedev\glpl D:\Gamedev\glpl\cmake-build-debug D:\Gamedev\glpl\cmake-build-debug D:\Gamedev\glpl\cmake-build-debug\CMakeFiles\glad.lib.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\glad.lib.dir\depend

