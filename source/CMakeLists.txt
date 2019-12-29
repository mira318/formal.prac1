cmake_minimum_required(VERSION 3.15)

project(1)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS  "--coverage")

add_executable(1 main_test.cpp)

add_subdirectory(googletest-master)
include_directories(googletest-master/googletest/include)
include_directories(googletest-master/googlemock/include)

target_link_libraries(1 gtest gtest_main)
