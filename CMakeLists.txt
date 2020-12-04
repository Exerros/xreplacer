cmake_minimum_required(VERSION 2.8)

project(everypixel_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_BUILD_TYPE RELEASE) # DEBUG / RELEASE
set(TESTS BUILD_TESTS) # BUILD_TESTS / NOT_BUILD_TESTS only in upper bound

add_compile_options(
        -Wall
        -g
)

#set the project variables
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(TESTS_DIR "${PROJECT_SOURCE_DIR}/tests")
set(BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}")

#configure cmake_variables
configure_file("${INCLUDE_DIR}/cmake_variables.hpp.in"
               "${INCLUDE_DIR}/cmake_variables.hpp")

#configure and build program library
file(GLOB_RECURSE ASSIGMENT_SRC "${SRC_DIR}/*.cpp")
add_library(assignment STATIC ${ASSIGMENT_SRC})
target_include_directories(assignment PUBLIC ${INCLUDE_DIR})
target_link_libraries(assignment stdc++fs pthread)

#configure and build tests library
if(TESTS MATCHES BUILD_TESTS)
    add_library(tests STATIC "${TESTS_DIR}/src")
    target_include_directories(tests PUBLIC "${TESTS_DIR}/include")
    target_link_libraries(tests assignment)
endif()

#linking and build program
add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} assignment)
if(TESTS MATCHES BUILD_TESTS)
    target_link_libraries(${PROJECT_NAME} tests)
endif()
