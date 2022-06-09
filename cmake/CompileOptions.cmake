# Compile options

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wpedantic -g -fno-omit-frame-pointer)

if(WHEELS_DEVELOPER)
    message(STATUS "Turn warnings into errors")
    add_compile_options(-Werror)
endif()
