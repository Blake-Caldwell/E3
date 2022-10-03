add_subdirectory(glad)
add_subdirectory(glfw)

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC
    glad/include
    glfw/include
)