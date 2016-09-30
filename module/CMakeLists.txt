set(PROJECT pam_stepic)

file(GLOB SOURCES
        "*.h"
        "*.cpp"
        )

add_library(${PROJECT} SHARED ${SOURCES})
target_link_libraries(${PROJECT} -lpam -lcap -ljsoncpp -lboost_program_options)