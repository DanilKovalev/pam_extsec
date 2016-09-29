include_directories(${CMAKE_HOME_DIRECTORY}/module)

set(PROJECT pam_stepic_tests)

file(GLOB SOURCES
        "*.h"
        "*.cpp"
        )

add_executable(${PROJECT} ${SOURCES})
target_link_libraries(${PROJECT} pam_stepic -lcppunit)


add_test(NAME "${PROJECT}"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND ${TEST_OUTPUT_PATH}/${PROJECT}
        )

set_target_properties(${PROJECT} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_PATH})
