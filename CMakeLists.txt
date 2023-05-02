cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(helloworld VERSION ${PROJECT_VESRION} LANGUAGES CXX)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/version.h)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/googletest-release-1.12.1)

file(GLOB_RECURSE CLI_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*)
file(GLOB_RECURSE LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/lib/*)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "Source" FILES ${CLI_SRC} ${LIB_SRC})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(
    helloworld
    ${LIB_SRC}
)

add_executable(
    helloworld_cli
    ${CLI_SRC}
)
target_link_libraries(
    helloworld_cli
    helloworld
)

include(GoogleTest)
enable_testing()

add_executable(
    test_version
    tests/test_version.cpp
    )

target_link_libraries(
    test_version
    helloworld
    GTest::gtest_main
    )

if (MSVC)
    target_compile_options(helloworld_cli PRIVATE
        /W4
    )
    target_compile_options(helloworld PRIVATE
        /W4
    )
    target_compile_options(test_version PRIVATE
        /W4
    )
else ()
    target_compile_options(helloworld_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(helloworld PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

gtest_discover_tests(test_version)
