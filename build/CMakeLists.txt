include_directories (../lib)

add_executable(2d_game main.cpp)

target_link_libraries(2d_game
subsystem_1
world
CppUtils
pthread
rt
gcov
ssl
mysqlclient )
