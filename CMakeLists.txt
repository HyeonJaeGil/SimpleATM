cmake_minimum_required(VERSION 3.14)
project(atm)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -g -BUILD_TEST")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

option(BUILD_TEST "Build test" ON)
IF(BUILD_TEST)
    add_definitions(-DBUILD_TEST)
    add_executable(test_atm test_atm.cpp atm.cpp)
    target_link_libraries(test_atm gtest_main)
ENDIF(BUILD_TEST)