cmake_minimum_required(VERSION 2.8)

project(everypixel_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_BUILD_TYPE Debug)

add_compile_options(
        -Wall
        -g
)

#set the project variables
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}")

#configure and build program library
file(GLOB_RECURSE TEST_SRC "${SRC_DIR}/*.cpp")
add_library(test STATIC ${TEST_SRC})
target_include_directories(test PUBLIC ${INCLUDE_DIR})

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} test_core)
