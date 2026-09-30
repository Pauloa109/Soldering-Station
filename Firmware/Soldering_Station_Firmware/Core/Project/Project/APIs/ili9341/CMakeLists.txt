target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    # Add user defined include paths
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(${CMAKE_PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/fonts.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ili9341.c
)
