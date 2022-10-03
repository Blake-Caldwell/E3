cmake_minimum_required( VERSION 3.8)

SET(PROJECT_NAME Game_Of_Life)
project(${PROJECT_NAME})

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
add_subdirectory(lib)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIRECTORY}/src)

target_link_libraries(${PROJECT_NAME} PUBLIC
glad
glfw
)