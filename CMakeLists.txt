cmake_minimum_required(VERSION 3.20)

project(LogParser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/Filters)

set(LIB_SOURCES
    src/CliParser.cpp
    src/FileManager.cpp
    src/LogProcessor.cpp
    src/Filters/RegexMatchFilter.cpp
    src/Filters/RegexSearchFilter.cpp
    src/Filters/LevelFilter.cpp
    src/Filters/CompositeFilter.cpp
    src/Filters/ExcludeFilter.cpp
    src/Filters/ExcludeRegexFilter.cpp
)

# create library for this project and tests
add_library(LogParserLib ${LIB_SOURCES})
target_include_directories(LogParserLib PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(LogParser src/main.cpp)
target_link_libraries(LogParser PRIVATE LogParserLib)

# if build test option is on, tests will be built
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
