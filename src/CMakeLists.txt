set(CMAKE_CXX_STANDARD 17)

include_directories(AFTER SYSTEM ./)

aux_source_directory(. SOURCES)
aux_source_directory(Core SOURCES)
aux_source_directory(Editor SOURCES)
aux_source_directory(Event SOURCES)
aux_source_directory(Renderer SOURCES)

add_executable(
    ${CMAKE_PROJECT_NAME}
    ${SOURCES}
)