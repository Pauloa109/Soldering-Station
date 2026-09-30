target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    # Add user defined include paths
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(${CMAKE_PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/fatfs_sd_card.c
    ${CMAKE_CURRENT_SOURCE_DIR}/sd_card.c
)
