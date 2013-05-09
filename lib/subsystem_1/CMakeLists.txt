# set(CMAKE_CXX_COMPILER "/usr/lib/colorgcc/bin/g++")

# TODO use/don't use different cflags when test/release build
set (CXX_FLAGS "-Wall -Wextra -pedantic -Weffc++ -Wshadow "
               "-Wpointer-arith -Wcast-qual "
               "-ggdb -fprofile-arcs -ftest-coverage -std=c++0x")
add_definitions( ${CXX_FLAGS} )

include_directories (.)
aux_source_directory(. SUBSYSTEM_1_SOURCES)

add_library (subsystem_1 SHARED ${SUBSYSTEM_1_SOURCES})
target_link_libraries(subsystem_1 gcov)