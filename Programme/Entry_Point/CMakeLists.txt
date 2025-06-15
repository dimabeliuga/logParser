file(GLOB ENTRY_POINT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${CMAKE_PROJECT_NAME} ${ENTRY_POINT_SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE 
                        ${MAIN_COMPONENTS_NAME}
                        ${FILTERS_LIBRARY_NAME}
                    )   
