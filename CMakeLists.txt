# Copyright 2022 Caleb Magruder

cmake_minimum_required(VERSION 3.22)

project(JSON)

set(CMAKE_CXX_STANDARD 20)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_CXX_CPPLINT "cpplint;--quiet;--exclude=${CMAKE_BINARY_DIR}/*")
  set(CMAKE_CXX_CPPCHECK "cppcheck;--quiet;--suppress=*:${CMAKE_BINARY_DIR}/*")
endif()

# Build JSON Library
add_library(JSON SHARED src/JSON.cpp
                        src/Array.cpp
                        src/Object.cpp
                        src/Variant.cpp)
target_include_directories(JSON PUBLIC include)

# If submodule, skip tests and google test dependency.
if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    # Fetch & Build Google Test Depencency
    include(FetchContent)
    FetchContent_Declare(
        GoogleTest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        main
    )
    set(BUILD_GMOCK OFF)
    FetchContent_MakeAvailable(GoogleTest)

    # Tests
    enable_testing()
    add_subdirectory(tests)
endif()

# Build Package
set(package_files include/ src/ CMakeLists.txt LICENSE VERSION)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-src.zip
                   COMMAND ${CMAKE_COMMAND} -E
                     tar c ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-src.zip
                     --format=zip -- ${package_files}
                   WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                   DEPENDS ${package_files})
add_custom_target(${PROJECT_NAME}_package
                  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-src.zip)
