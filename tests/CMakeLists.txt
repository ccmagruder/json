# Copyright 2022 Caleb Magruder

project(JSON)

add_executable(tJSON tJSON.cpp)
add_executable(tArray tArray.cpp)
add_executable(tObject tObject.cpp)
add_executable(tVariant tVariant.cpp)

target_include_directories(tJSON PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(tArray PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(tObject PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(tVariant PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(tJSON JSON gtest gtest_main)
target_link_libraries(tArray JSON gtest gtest_main)
target_link_libraries(tObject JSON gtest gtest_main)
target_link_libraries(tVariant JSON gtest gtest_main)

add_test(NAME tJSON WORKING_DIRECTORY tests COMMAND tJSON)
add_test(NAME tArray WORKING_DIRECTORY tests COMMAND tArray)
add_test(NAME tObject WORKING_DIRECTORY tests COMMAND tObject)
add_test(NAME tVariant WORKING_DIRECTORY tests COMMAND tVariant)

configure_file(validTypes.json validTypes.json COPYONLY)
