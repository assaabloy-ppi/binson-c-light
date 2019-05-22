cmake_minimum_required(VERSION 2.8)
project(binson-c-light)
enable_language(C)
enable_language(CXX)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
find_package(Sanitizers)
include(cmake/coverage.cmake)

option(BUILD_TESTS "Build tests" OFF)
option(WITH_PRINT "Add support for print" ON)
option(WITH_CPP "Add support for C++ wrapper" ON)
option(BUILD_EXAMPLES "Build examples" OFF)
option(BUILD_FUZZ_TESTS "Build fuzz tests" OFF)

if(WITH_PRINT)
  add_definitions(-DBINSON_PARSER_WITH_PRINT)
endif(WITH_PRINT)

add_subdirectory(src)
include_directories(include)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(utest)
    set(BUILD_FUZZ_TESTS ON)
endif(BUILD_TESTS)

if(BUILD_FUZZ_TESTS)
  add_subdirectory(fuzz-test)
endif(BUILD_FUZZ_TESTS)

if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif(BUILD_EXAMPLES)
