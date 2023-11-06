cmake_minimum_required(VERSION 3.28)

project(
VENGINE
VERSION 1.0
LANGUAGES C
)

add_executable(${PROJECT_NAME} main.c)

include_directories(Deps/glfw-3.3.8/include)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(Deps/glfw-3.3.8)
target_link_libraries(${PROJECT_NAME} glfw)
