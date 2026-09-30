add_subdirectory(Configurator)
add_subdirectory(Debug)
add_subdirectory(Returns)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)