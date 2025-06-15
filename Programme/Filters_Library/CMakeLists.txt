file(GLOB FILTERS_LIBRARY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

set(FILTERS_LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/")

add_library(${FILTERS_LIBRARY_NAME} ${FILTERS_LIBRARY_SOURCES})

target_include_directories(${FILTERS_LIBRARY_NAME} PUBLIC 
                            ${FILTERS_LIBRARY_HEADERS}
                        )

target_link_libraries(${FILTERS_LIBRARY_NAME} PUBLIC 
                        ${MAIN_COMPONENTS_NAME}
                    )