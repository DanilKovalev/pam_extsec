cmake_minimum_required(VERSION 2.7)
project(pam_stepic)

set(PROJECT pam_stepic)

set ("${PROJECT}_BINARY_DIR"  bin)
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/${${PROJECT}_BINARY_DIR})
set (TEST_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/${${PROJECT}_BINARY_DIR}/test)
set (EXAMPLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/${${PROJECT}_BINARY_DIR}/example)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Weffc++ -Wunused-result")

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE RELEASE)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}  -D_DEBUG -g ")

message(${CMAKE_CXX_FLAGS_DEBUG})

enable_testing()
add_subdirectory(module)
add_subdirectory(test)
