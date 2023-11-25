# Copyright 2023 Caleb Magruder

cmake_minimum_required(VERSION 3.22)

project(JSON)

set(CMAKE_CXX_STANDARD 20)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_CXX_CPPLINT "cpplint;--quiet;--exclude=${CMAKE_BINARY_DIR}/*")
  set(CMAKE_CXX_CPPCHECK "cppcheck;--quiet;--suppress=*:${CMAKE_BINARY_DIR}/*")
endif()

# Build JSON Library
add_library(JSON SHARED src/JSON.cpp
                        src/Variant.cpp)
target_include_directories(JSON PUBLIC include)

