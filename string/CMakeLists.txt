cmake_minimum_required(VERSION 3.0.0)
project(makeString VERSION 0.1.0)

add_executable(makeString main.cpp makeString.cpp makeString.h)

set(CMAKE_CXX_EXTENSIONS OFF)      # no vendor-specific extensions
set_property(TARGET makeString PROPERTY CXX_STANDARD 20)

if (MSVC)
    target_compile_options(makeString PUBLIC /W4 /WX /Za /permissive-)
else()
    target_compile_options(makeString PUBLIC -Wall -Wextra -pedantic -Werror)
endif()