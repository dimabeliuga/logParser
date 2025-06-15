cmake_minimum_required(VERSION 3.20)

project(LogParser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MAIN_COMPONENTS_NAME "MAIN_COMPONENTS")
set(FILTERS_LIBRARY_NAME "FILTERS_LIBRARY")

SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/MAIN
        CACHE PATH
        "Director for dynamical libraries .so/.dll"
    )

SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/MAIN
        CACHE PATH
        "Director for .exe/.out"
    )

SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/lib
        CACHE PATH
        "Directory for static libraries .a/.lib"
    )

add_subdirectory(Programme)

# if build test option is on, tests will be built
option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

message("[INFO] TESTS enable - ${BUILD_TESTS}")