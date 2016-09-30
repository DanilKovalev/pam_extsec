cmake_minimum_required(VERSION 2.7)
project(pam_stepic)

set(PROJECT pam_stepic)

set (OUTPUT_DIR ${CMAKE_HOME_DIRECTORY}/output)
set (EXECUTABLE_OUTPUT_PATH ${OUTPUT_DIR}/bin)
set (TEST_OUTPUT_PATH ${OUTPUT_DIR}/test)
set (EXAMPLE_OUTPUT_PATH ${OUTPUT_DIR}/example)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Weffc++ -Wunused-result")

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE RELEASE)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}  -D_DEBUG -g ")

enable_testing()
add_subdirectory(module)
add_subdirectory(test)
