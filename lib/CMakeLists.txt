add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(glm)


target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC
    glad/include
    glfw/include
    glm
)