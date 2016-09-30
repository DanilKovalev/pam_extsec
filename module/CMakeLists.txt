set(PROJECT pam_stepic)


find_library(LIB_PAM pam )
if(NOT LIB_PAM)
    message(FATAL_ERROR "pam library not found")
endif()

find_library(LIB_CAP pam )
if(NOT LIB_CAP)
    message(FATAL_ERROR "cap library not found")
endif()

find_library(LIB_JSONCPP jsoncpp )
if(NOT LIB_JSONCPP)
    message(FATAL_ERROR "jsoncpp library not found")
endif()

find_library(LIB_PROGRAM_OPTIONS boost_program_options )
if(NOT LIB_PROGRAM_OPTIONS)
    message(FATAL_ERROR "boost_program_options library not found")
endif()

file(GLOB SOURCES
        "*.h"
        "*.cpp"
        )

add_library(${PROJECT} SHARED ${SOURCES})
target_link_libraries(${PROJECT} -lpam -lcap -ljsoncpp -lboost_program_options)