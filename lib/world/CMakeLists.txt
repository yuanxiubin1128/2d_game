include_directories (.)
aux_source_directory(. WORLD_SOURCES)

add_library (world SHARED ${WORLD_SOURCES})
target_link_libraries(world png)