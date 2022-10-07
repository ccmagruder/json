# Copyright 2022 Caleb Magruder
cmake_minimum_required(VERSION 3.22)

project(JSON)

set(CMAKE_CXX_STANDARD 17)

add_library(JSON SHARED ${CMAKE_SOURCE_DIR}/src/JSON.cpp)

target_include_directories(JSON PUBLIC ${CMAKE_SOURCE_DIR}/include)
