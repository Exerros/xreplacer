################################################################################
#
# TODO text 
#
################################################################################

cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(xreplacer
        VERSION 1.0.0
        HOMEPAGE_URL "https://github.com/exerros/fileparser"
        LANGUAGES CXX)


################################################################################
#
# TODO text

set(XREPLACER_INCLUDE_DIR       "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(XREPLACER_SOURCE_DIR        "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(XREPLACER_TESTS_DIR         "${CMAKE_CURRENT_SOURCE_DIR}/tests")
set(XREPLACER_CMAKE_DIR         "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(XREPLACER_THIRD_PARTY_DIR   "${CMAKE_CURRENT_SOURCE_DIR}/third_party")


################################################################################
#
# TODO text

option(XREPLACER_BUILD_SHARED "" ON)
option(XREPLACER_BUILD_DOCS "" ON)
option(XREPLACER_BUILD_TESTS "" ON)
option(XREPLACER_COVERAGE "" ON)


################################################################################
#
# TODO text

configure_file("${INCLUDE_DIR}/cmake_variables.hpp.in"
               "${INCLUDE_DIR}/cmake_variables.hpp" @ONLY)


################################################################################
#
# TODO text

if(XREPLACER_BUILD_SHARED)
    set(XREPLACER_LIBRARY_TYPE SHARED)
else()
    set(XREPLACER_LIBRARY_TYPE STATIC)
endif()

add_library(xrep ${XREPLACER_LIBRARY_TYPE})
add_library(xreplacer::xreplacer ALIAS xrep)

file(GLOB_RECURSE XREPLACER_SRC "${XREPLACER_SOURCE_DIR}/*.cpp")
target_sources(xrep ${XREPLACER_SRC})
target_include_directories(xrep 
    PUBLIC
        $<INSTALL_INTERFACE:include/>
        $<BUILD_INTERFACE:${XREPLACER_INCLUDE_DIR}>)

set_target_properties(xreplacer PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
    CMAKE_BUILD_TYPE RELEASE)

target_compile_features(xreplacer cxx_std_17 filesystem)
target_compile_options(xreplacer 
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic)

target_link_libraries(xreplacer stdc++fs pthread)


################################################################################
#
# TODO text

add_executable(xreplacer_exe "${CMAKE_PROJECT_SOURCE_DIR}/main.cpp")
target_link_libraries(xreplacer_exe xreplacer)


################################################################################
#
# TODO text

# TODO build tests
# TODO ctest gtest my-cmake

if(XREPLACER_BUILD_TESTS)
    
endif()


################################################################################
#
# TODO text

# TODO build docs

if(XREPLACER_BUILD_DOCS)

endif()


################################################################################
#
# OLD
#
################################################################################

#set(CMAKE_BUILD_TYPE release)
#set(BUILD_TESTS ON)

#add_compile_options(
#        -Wall
#        -g
#        -std=c++17
#)

####set the project variables
#set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
#set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
#set(TESTS_INCLUDE "${PROJECT_SOURCE_DIR}/tests/include")
#set(TESTS_SRC "${PROJECT_SOURCE_DIR}/tests/src")
#set(BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}")

####configure cmake_variables

####configure and build program library
#file(GLOB_RECURSE ASSIGMENT_SRC "${SRC_DIR}/*.cpp")
#add_library(assignment STATIC ${ASSIGMENT_SRC})
#target_include_directories(assignment PUBLIC ${INCLUDE_DIR})

#####configure and build tests library
#if(BUILD_TESTS)
#    file(GLOB_RECURSE TESTS_SRC "${TESTS_SRC}/*.cpp")
#    add_library(tests STATIC ${TESTS_SRC})
#    target_include_directories(tests PUBLIC ${TESTS_INCLUDE})
#    target_link_libraries(tests assignment)
#endif()

####linking and build program
#add_executable(${PROJECT_NAME} "main.cpp")
#if(BUILD_TESTS)
#    target_link_libraries(${PROJECT_NAME} assignment tests)
#else()
#    target_link_libraries(${PROJECT_NAME} assignment)
#endif()
