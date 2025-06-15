function(add_test_executable test_name test_dir extra_libs)
    file(GLOB TEST_SRC CONFIGURE_DEPENDS ${test_dir}/*.cpp)

    add_executable(${test_name} ${TEST_SRC})

    target_link_libraries(${test_name} 
                        PRIVATE 
                        gtest_main 
                        ${extra_libs}
                        )
    include(GoogleTest)
    gtest_discover_tests(${test_name})
endfunction()

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)


file(GLOB TEST_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR}/*
                    )
foreach(test_dir ${TEST_DIRS})
    if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${test_dir}")
        add_subdirectory(${test_dir})
        message("[Test] subdirectory [${test_dir}] has been added")
    endif()
endforeach()