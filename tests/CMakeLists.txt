cmake_minimum_required(VERSION 3.20)
project(LogParserTests LANGUAGES CXX)

find_package(GTest CONFIG REQUIRED)
if (NOT GTest_FOUND)
    message(FATAL_ERROR "GoogleTest not found. Please install GoogleTest to run tests")
endif()

# find all test files in the current directory
file(GLOB TEST_SOURCES *.cpp)

foreach(test_file ${TEST_SOURCES})
    # extract file name (without exstansion)
    get_filename_component(test_name ${test_file} NAME_WE)
    
    # create executable for each test file 
    add_executable(${test_name} ${test_file})
    
    target_include_directories(${test_name} PRIVATE ${CMAKE_SOURCE_DIR}/include)
    
    # link test with libraries
    target_link_libraries(${test_name} PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main LogParserLib)

    # add test to the ctest
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
