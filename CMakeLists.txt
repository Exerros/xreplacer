cmake_minimum_required(VERSION 2.8)
project(everypixel_test)

set(CMAKE_BUILD_TYPE release)
set(BUILD_TESTS ON)

add_compile_options(
        -Wall
        -g
        -std=c++17
)

#set the project variables
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(TESTS_INCLUDE "${PROJECT_SOURCE_DIR}/tests/include")
set(TESTS_SRC "${PROJECT_SOURCE_DIR}/tests/src")
set(BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}")

#configure cmake_variables
configure_file("${INCLUDE_DIR}/cmake_variables.hpp.in"
               "${INCLUDE_DIR}/cmake_variables.hpp" @ONLY)

#configure and build program library
file(GLOB_RECURSE ASSIGMENT_SRC "${SRC_DIR}/*.cpp")
add_library(assignment STATIC ${ASSIGMENT_SRC})
target_include_directories(assignment PUBLIC ${INCLUDE_DIR})
target_link_libraries(assignment stdc++fs pthread)

#configure and build tests library
if(BUILD_TESTS)
    file(GLOB_RECURSE TESTS_SRC "${TESTS_SRC}/*.cpp")
    add_library(tests STATIC ${TESTS_SRC})
    target_include_directories(tests PUBLIC ${TESTS_INCLUDE})
    target_link_libraries(tests assignment)
endif()

#linking and build program
add_executable(${PROJECT_NAME} "main.cpp")
if(BUILD_TESTS)
    target_link_libraries(${PROJECT_NAME} assignment tests)
else()
    target_link_libraries(${PROJECT_NAME} assignment)
endif()
