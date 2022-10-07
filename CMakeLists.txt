# Copyright 2022 Caleb Magruder

cmake_minimum_required(VERSION 3.22)

project(JSON)

set(CMAKE_CXX_STANDARD 20)

# Build JSON Library
add_library(JSON SHARED src/JSON.cpp
                        src/Variant.cpp)
target_include_directories(JSON PUBLIC include)

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

    enable_testing()
    add_subdirectory(tests)
endif()
