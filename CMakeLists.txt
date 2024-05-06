cmake_minimum_required(VERSION 3.13)

project(raytracer VERSION 1.0 LANGUAGES CXX)

set(EXECUTABLE_OUTPUT_PATH "../../bin/")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/glew)
add_subdirectory(lib/glfw)
add_subdirectory(lib/glm)
add_subdirectory(src)

include_directories(lib/glew/include)
include_directories(lib/glfw/include)
include_directories(src)

target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    libglew_static
    glfw
    ${OPENGL_gl_LIBRARY}
    ${GLFW_LIBRARIES}
    glm::glm
)

find_package(OpenGL REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} OpenGL::GL)