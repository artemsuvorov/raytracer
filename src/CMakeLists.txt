set(CMAKE_CXX_STANDARD 17)

aux_source_directory(
    ./
    SOURCES
)

add_executable(
    ${CMAKE_PROJECT_NAME}
    ${SOURCES}
)