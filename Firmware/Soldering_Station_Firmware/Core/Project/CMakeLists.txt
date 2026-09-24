add_subdirectory(APP)
add_subdirectory(APIs)
add_subdirectory(Modules)

target_include_directories(${CMAKE_PROJECT_NAME} INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc
)
