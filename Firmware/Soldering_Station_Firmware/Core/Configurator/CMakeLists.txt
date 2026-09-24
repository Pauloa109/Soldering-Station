add_subdirectory(System)
add_subdirectory(Internal)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    # Add user defined include paths
    ${CMAKE_CURRENT_SOURCE_DIR}
)