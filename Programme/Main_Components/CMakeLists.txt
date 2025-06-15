file(GLOB MAIN_COMPONENTS_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

set(MAIN_COMPONENTS_HEADERS "include/")

add_library(${MAIN_COMPONENTS_NAME} ${MAIN_COMPONENTS_SOURCES})

target_include_directories(${MAIN_COMPONENTS_NAME} PUBLIC 
                            ${MAIN_COMPONENTS_HEADERS}
                        )


