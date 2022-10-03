cmake_minimum_required( VERSION 3.8)

SET(PROJECT_NAME Game_Of_Life)
project(${PROJECT_NAME})

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
add_executable (${PROJECT_NAME} ${SOURCES} "lib/glad/src/glad.c")
add_subdirectory(lib)



target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIRECTORY}/src)

target_link_libraries(${PROJECT_NAME} PUBLIC
glad
glfw
glm
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)

