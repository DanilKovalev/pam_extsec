cmake_minimum_required(VERSION 2.7)
project(pam_stepic)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Weffc++ -Wunused-result")

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE RELEASE)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}  -D_DEBUG -g ")

message(${CMAKE_CXX_FLAGS_DEBUG})

add_subdirectory(module)
add_subdirectory(tests)
