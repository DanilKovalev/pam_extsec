set(PROJECT pam_stepic_tests)

file(GLOB SOURCES
        "*.h"
        "*.cpp"
        )

include_directories(${CMAKE_HOME_DIRECTORY}/module)
add_executable(${PROJECT} ${SOURCES})
target_link_libraries(${PROJECT} pam_stepic -lcppunit)