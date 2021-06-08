################################################################################
#                                                                              #
# This program was developed in December 2020 as a test job for everypixel.    #
# Xreplacer is capable of multithreading the file tree of any nesting and      #
# making replacements according to the configuration file.                     #
# Now in June 2021 I am updating this project to correct the existing flaws.   #
#                                                                              #
################################################################################

cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(xreplacer
        VERSION 1.0.0
        HOMEPAGE_URL "https://github.com/exerros/xreplacer"
        LANGUAGES CXX)


################################################################################
#
# This section sets the main variables used to build the project.

set(XREPLACER_INCLUDE_DIR       "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(XREPLACER_SOURCE_DIR        "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(XREPLACER_TESTS_DIR         "${CMAKE_CURRENT_SOURCE_DIR}/tests")
set(XREPLACER_CMAKE_MODULES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(XREPLACER_THIRD_PARTY_DIR   "${CMAKE_CURRENT_SOURCE_DIR}/third_party")


################################################################################
#
# This section is responsible for the optional build values, change them as you
# need.

option(XREPLACER_BUILD_SHARED
       "Assemble the program library as a dynamic library" ON)
option(XREPLACER_BUILD_DOCS "Build documentation when assembling a project" ON)
option(XREPLACER_BUILD_TESTS "Build tests when building a project." ON)
option(XREPLACER_COVERAGE "Checking code coverage with tests." ON)


################################################################################
#
#

set(BUILD_SHARED_LIBS ON)
add_subdirectory("${XREPLACER_THIRD_PARTY_DIR}/pugixml")


################################################################################
#
# This section is responsible for assembling the library with the main modules
# of the program.

if(XREPLACER_BUILD_SHARED)
    set(XREPLACER_LIBRARY_TYPE SHARED)
else()
    set(XREPLACER_LIBRARY_TYPE STATIC)
endif()

add_library(xrep ${XREPLACER_LIBRARY_TYPE})
add_library(xreplacer::xreplacer ALIAS xrep)

file(GLOB_RECURSE XREPLACER_SRC "${XREPLACER_SOURCE_DIR}/*.cpp")
target_sources(xrep PRIVATE ${XREPLACER_SRC})
target_include_directories(xrep 
    PUBLIC
        $<INSTALL_INTERFACE:include/>
        $<BUILD_INTERFACE:${XREPLACER_INCLUDE_DIR}>)

set_target_properties(xrep PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
    CMAKE_BUILD_TYPE RELEASE)

target_compile_features(xrep
    INTERFACE
        cxx_std_17
        cxx_constexpr
        cxx_decltype
        cxx_auto_type)
target_compile_options(xrep
    INTERFACE
        -Wall
        -Wextra
        -Wpedantic)

target_link_libraries(xrep pugixml::pugixml stdc++fs pthread)


################################################################################
#
# This section is responsible for building the application to be launched.

add_executable(xreplacer "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
target_link_libraries(xreplacer xrep)

set_target_properties(xreplacer PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
    CMAKE_BUILD_TYPE RELEASE)

################################################################################
#
# This section is responsible for assembling the tests and preparing the CTest
# module.

# TODO build tests
# TODO ctest gtest my-cmake

if(XREPLACER_BUILD_TESTS)
    include(CTest)
    enable_testing()

        set(TEST_HAS_PTHREAD 1)
        add_subdirectory("${XREPLACER_THIRD_PARTY_DIR}/gtest")
        set(LIBS_TO_LINK xrep gtest)

        include("${XREPLACER_CMAKE_MODULES_DIR}/functions/test_builder.cmake")
        build_tests(${XREPLACER_TESTS_DIR} ${LIBS_TO_LINK})
endif()


################################################################################
#
# This section is responsible for building the documentation when building the
# project.

# TODO build docs

if(XREPLACER_BUILD_DOCS)

endif()


################################################################################
#
# This section is responsible for installing the application on the system.

# TODO install


################################################################################
#
# This section is responsible for installing the application on the system.

# TODO cpack



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
