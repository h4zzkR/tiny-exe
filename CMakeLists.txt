cmake_minimum_required(VERSION 3.14)

project(exe)

option(EXE_TESTS "Enable EXE tests" OFF)
option(EXE_DEVELOPER "EXE development mode" OFF)

include(cmake/ClangFormat.cmake)
include(cmake/ClangTidy.cmake)

include(cmake/CompileOptions.cmake)

include(cmake/Platform.cmake)
include(cmake/Processor.cmake)
include(cmake/Arch.cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

add_subdirectory(exe)

if(EXE_TESTS OR EXE_DEVELOPER)
    add_subdirectory(tests)
endif()
