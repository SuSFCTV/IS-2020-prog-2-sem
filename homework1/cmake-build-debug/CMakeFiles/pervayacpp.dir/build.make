# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\misha\Desktop\labs\prog\pervayacpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\misha\Desktop\labs\prog\pervayacpp\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\pervayacpp.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\pervayacpp.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\pervayacpp.dir\flags.make

CMakeFiles\pervayacpp.dir\main.cpp.obj: CMakeFiles\pervayacpp.dir\flags.make
CMakeFiles\pervayacpp.dir\main.cpp.obj: ..\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\misha\Desktop\labs\prog\pervayacpp\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pervayacpp.dir/main.cpp.obj"
	C:\PROGRA~2\MIB055~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\pervayacpp.dir\main.cpp.obj /FdCMakeFiles\pervayacpp.dir\ /FS -c C:\Users\misha\Desktop\labs\prog\pervayacpp\main.cpp
<<

CMakeFiles\pervayacpp.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pervayacpp.dir/main.cpp.i"
	C:\PROGRA~2\MIB055~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe > CMakeFiles\pervayacpp.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\misha\Desktop\labs\prog\pervayacpp\main.cpp
<<

CMakeFiles\pervayacpp.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pervayacpp.dir/main.cpp.s"
	C:\PROGRA~2\MIB055~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\pervayacpp.dir\main.cpp.s /c C:\Users\misha\Desktop\labs\prog\pervayacpp\main.cpp
<<

# Object files for target pervayacpp
pervayacpp_OBJECTS = \
"CMakeFiles\pervayacpp.dir\main.cpp.obj"

# External object files for target pervayacpp
pervayacpp_EXTERNAL_OBJECTS =

pervayacpp.exe: CMakeFiles\pervayacpp.dir\main.cpp.obj
pervayacpp.exe: CMakeFiles\pervayacpp.dir\build.make
pervayacpp.exe: CMakeFiles\pervayacpp.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\misha\Desktop\labs\prog\pervayacpp\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pervayacpp.exe"
	"C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\pervayacpp.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\mt.exe --manifests  -- C:\PROGRA~2\MIB055~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\pervayacpp.dir\objects1.rsp @<<
 /out:pervayacpp.exe /implib:pervayacpp.lib /pdb:C:\Users\misha\Desktop\labs\prog\pervayacpp\cmake-build-debug\pervayacpp.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\pervayacpp.dir\build: pervayacpp.exe

.PHONY : CMakeFiles\pervayacpp.dir\build

CMakeFiles\pervayacpp.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\pervayacpp.dir\cmake_clean.cmake
.PHONY : CMakeFiles\pervayacpp.dir\clean

CMakeFiles\pervayacpp.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\misha\Desktop\labs\prog\pervayacpp C:\Users\misha\Desktop\labs\prog\pervayacpp C:\Users\misha\Desktop\labs\prog\pervayacpp\cmake-build-debug C:\Users\misha\Desktop\labs\prog\pervayacpp\cmake-build-debug C:\Users\misha\Desktop\labs\prog\pervayacpp\cmake-build-debug\CMakeFiles\pervayacpp.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\pervayacpp.dir\depend

