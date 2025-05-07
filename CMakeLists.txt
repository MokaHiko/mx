cmake_minimum_required(VERSION 3.0.0...3.10)
project(mx VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(MX_BUILD_SHARED_LIBS OFF CACHE BOOL "MX build shared libraries.")

if(MX_BUILD_SHARED_LIBS)
    add_library(mx SHARED third_party/murmur_hash/murmur_hash.c src/mx.c src/mx_log.c src/mx_memory.c src/mx_file.c src/mx_math.c src/mx_math_mtx.c src/mx_darray.c src/mx_hash.c)
    target_compile_definitions(mx PUBLIC MX_EXPORTS)
else()
    add_library(mx STATIC third_party/murmur_hash/murmur_hash.c src/mx.c src/mx_log.c src/mx_memory.c src/mx_file.c src/mx_math.c src/mx_math_mtx.c src/mx_darray.c src/mx_hash.c)
endif()

target_include_directories(mx PUBLIC include)
target_include_directories(mx PUBLIC third_party)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Building on Windows")
    target_compile_definitions(mx PUBLIC MX_WIN32=1)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Building on Linux")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "Building on macOS")
    target_compile_definitions(mx PUBLIC MX_MACOS=1)
else()
    message(WARNING "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

if(CMAKE_C_COMPILER_ID MATCHES "Clang")
    target_compile_definitions(mx PUBLIC MX_CLANG=1)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(mx PUBLIC MX_DEBUG=1)
else()
    target_compile_definitions(mx PUBLIC MX_DEBUG=0)
endif()
