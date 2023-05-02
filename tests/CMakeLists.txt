cmake_minimum_required(VERSION 3.11)
project(helloworld_units LANGUAGES CXX )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)

enable_testing()
add_executable(
    test_version
    test_version.cpp
    )

target_link_libraries(
    test_version
    helloworld
    GTest::gtest_main
    )
if (MSVC)
    target_compile_options(test_version PRIVATE
        /W4
    )
else ()
    target_compile_options(test_version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

include(GoogleTest)
gtest_discover_tests(test_version)
