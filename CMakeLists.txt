cmake_minimum_required(VERSION 3.28)

project(
VENGINE
VERSION 1.0
LANGUAGES C
)

add_executable(${PROJECT_NAME} main.c)

target_include_directories(${PROJECT_NAME} 
PRIVATE Deps/glfw-3.3.8/include Deps/Vulkan/Include)

#TODO: this sdk library .lib file will just work with x64 windows !!!
target_link_directories(${PROJECT_NAME} PRIVATE Deps/Vulkan/Lib)
target_link_libraries(${PROJECT_NAME} vulkan-1.lib)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(Deps/glfw-3.3.8)
target_link_libraries(${PROJECT_NAME} glfw)
