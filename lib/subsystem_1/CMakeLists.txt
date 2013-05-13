include_directories (.)
aux_source_directory(. SUBSYSTEM_1_SOURCES)

add_library (subsystem_1 SHARED ${SUBSYSTEM_1_SOURCES})
target_link_libraries(subsystem_1)