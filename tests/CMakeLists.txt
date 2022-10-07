# Copyright 2022 Caleb Magruder

project(JSON)

add_executable(tJSON tJSON.cpp)

target_include_directories(tJSON PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(tJSON JSON gtest gtest_main)

add_test(NAME tJSON
         WORKING_DIRECTORY tests
         COMMAND tJSON)

configure_file(validTypes.json validTypes.json COPYONLY)
