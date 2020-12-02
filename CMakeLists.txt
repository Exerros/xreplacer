cmake_minimum_required(VERSION 2.8)

project(everypixel_test)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED True)
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
file(GLOB_RECURSE TEST_CORE_SRC "${SRC_DIR}/*.cpp")
add_library(test_core STATIC ${TEST_CORE_SRC})
target_include_directories(test_core PUBLIC ${INCLUDE_DIR})

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} test_core)
